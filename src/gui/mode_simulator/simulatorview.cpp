//
// specify simulator view/scene objects
//

#include "simulatorview.hpp"

#include <QDebug>
#include <QFile>
#include <QScrollBar>
#include <QTextStream>


// public
SimulatorView::SimulatorView(QWidget * parent)
      : QGraphicsView(parent), s_scene(new AlgorithmLattice(this))
{
   // encompass 21 * 21 tiles
   s_scene->setSceneRect(-760,-575,4150,1655);
   setScene(s_scene);

   const qreal x= s_scene->sceneRect().x();
   const qreal y= s_scene->sceneRect().y();

   auto hbar= new QScrollBar(Qt::Horizontal, this);
   setHorizontalScrollBar(hbar);
   hbar->setSliderPosition((int) x - 25);

   auto vbar= new QScrollBar(Qt::Vertical, this);
   setVerticalScrollBar(vbar);
   vbar->setSliderPosition((int) y - 25);

   // realtime update of hypothetical lattice dimensions
   auto p_palette= s_scene->p_operators;
   connect(p_palette->measurement_buttons,&QButtonGroup::idClicked
         ,[this, p_palette](){
            latticeFromPatterns(
                  p_palette->possibleRows->currentText().toULong());
   });
   connect(p_palette->pattern_buttons,&QButtonGroup::idClicked
         ,[this, p_palette](const int id){
      unsigned long checkRow= p_palette->possibleRows->currentText().toULong();

      // to avoid nullptr: CNOT- upwards arrow (id: 6), downwards arrow (id: 7)
      (id == 6 && checkRow > 0) ? checkRow -= 1 : checkRow;
      if (id == 7){
         checkRow > 0 ? checkRow -= 1 : checkRow;
         swapProxy1= true;
      }
      latticeFromPatterns(checkRow);
   });
   connect(p_palette->p_addRow, &QPushButton::clicked
           , [this, p_palette](){ latticeFromPatterns(
      p_palette->possibleRows->currentText().toULong());
   });
}

// read instructions, format .txt
void SimulatorView::openAlgorithm(const QString & rfile) {
   QFile loadfile(rfile);
   // read conditions: read-only, text
   if (!loadfile.open(QIODevice::ReadOnly | QIODevice::Text)){
      qDebug() << "file is not open";
      return;
   }

   QTextStream inStream(&loadfile);

   // prepare view
   s_scene->clear();
   // reset columns counter
   auto n= sizeof(s_scene->columnAtRow) / sizeof(s_scene->columnAtRow[0]);
   memset(s_scene->columnAtRow, 0, n * s_scene->columnAtRow[0]);

   // place all tiles
   int savedRow;
   int lastRow {0};
   int savedCol;
   int lastCol {0};

   // see method, latticeFromPatterns: lattice dimension variables
   QString perimeter;
   unsigned long distance;

   QString tileData{inStream.readLine()};

   while (!tileData.isNull()) {
      QStringList tileSpecs= tileData.split(QChar(' '));

      // concatenate operators with white-spacing in name (e.g. 'sigma' 'x')
      if (tileSpecs.length() == 4){
         openSign= tileSpecs.at(0) % " " % tileSpecs.at(1);
         savedRow= tileSpecs.at(2).toInt();
         savedCol= tileSpecs.at(3).toInt();
      }
      else if (tileSpecs.length() == 3){
         openSign= tileSpecs.at(0);
         savedRow= tileSpecs.at(1).toInt();
         savedCol= tileSpecs.at(2).toInt();
      }
      else {   // see method, latticeFromPatterns: collect lattice dimensions
         perimeter= tileSpecs.at(0);
         distance= tileSpecs.at(1).toULong();
      }

      // accumulate the columns count of each row (inc. dummy CNOT target)
      if (savedCol > lastCol)
         lastCol= savedCol;
      // at each new row: set columnAtRow of the previous row, update 'switch
      //    rows' on the tile palette then clear variable, lastCol
      if (savedRow > lastRow){
         if (lastCol > savedCol)
            s_scene->columnAtRow[lastRow]= lastCol + 1;

         // update the QComboBox, 'switch rows'
         auto p_comboBox= s_scene->p_operators->possibleRows;
         auto rowValue = QString::number(savedRow);
         if (p_comboBox->findText(rowValue) == -1){
            p_comboBox->insertItem(savedRow, rowValue);
            // reset 'switch rows' display to the added row
            p_comboBox->setCurrentIndex(savedRow);
         }

         lastCol= 0;
         lastRow= savedRow;
      }

      // specify tile but ignore marker for dummy CNOT target (see method,
      // saveAlgorithm below)
      if (openSign != "CNOT_marker"){
         // reproduce tile
         p_tileType = new SignMeasure(openSign);
         p_tileType->setPos(nodeAddress[savedRow][savedCol]);

         s_scene->addItem(p_tileType);
      }
/*   TO DO: requires fix to NULL pointer at latticeFromPatterns
 *      // statistics of the (hypothetical) lattice underlying the algorithm at
 *      // save
 *      if (perimeter == "south")
 *         mStat= distance;
 *      if (perimeter == "east")
 *         nStat= distance;
*/
      tileData= inStream.readLine();
   }
   s_scene->columnAtRow[savedRow]= savedCol + 1;
   loadfile.close();
}

// read a quantum circuit file, format .json (schemata: 'native', which is
// adapted from ionQ; and Google Cirq, which is reformatted to the native
// schema). See comments of src/layout/io_circuit.cpp.
// NOTE: readCircuit will only insert readout tiles at a row with 20 tiles.
void SimulatorView::readCircuit(const QString & cjson) {
   // convert QString to utf8 string
   std::string cjson_utf8= cjson.toUtf8().constData();
   std::ifstream json_circuit {cjson_utf8};

   if (json_circuit.is_open()){
      using json= nlohmann::json;

      json parse_circuit= json::parse(json_circuit);   // create json object
      auto cirq_check= parse_circuit.find("cirq_type");

      json circuitToTiles;
      if (cirq_check != parse_circuit.end()){
         // format of input circuit json: cirq
         json ionq_schema= cirq_to_ionq_schema(parse_circuit);
         circuitToTiles= ionq_schema;
      }
         // format of input circuit json: ionQ
      else {
         if (non_adjacent_gate(parse_circuit))
            qDebug() << "process aborted: non-adjacent gate in circuit";

         circuitToTiles= parse_circuit;
      }

      auto implicitRow= sizeof(s_scene->columnAtRow) / sizeof(s_scene->columnAtRow[0]);
      // *** abort read: input circuit["moments"] exceeds the columns limit of
      //    simulator ***
      if (circuitToTiles["moments"] > implicitRow){
         qDebug() << "process aborted: count of circuit columns exceeds the "
                     "column limits of simulator";
         return ;
      }

      int qbits= circuitToTiles["qubits"];
      // *** abort read: the count of circuit rows exceeds the rows limit of
      //    simulator ***
      if (qbits > implicitRow){
         qDebug() << "process aborted: count of circuit rows exceeds the row "
                     "limits of simulator";
         return ;
      }

      // reset columns counter
      memset(s_scene->columnAtRow, 0, implicitRow * s_scene->columnAtRow[0]);

      // prepare view and initialise row 0
      s_scene->clear();
      p_tileType= new SignMeasure(s_scene->ket0);
      p_tileType->setPos(nodeAddress[0][0]);
      s_scene->addItem(p_tileType);

      s_scene->columnAtRow[0] += 1;

      // initialise rows 1+
      if (qbits > 1){
         for (int i= 0; i < (qbits - 1); ++i) {
            s_scene->addRow();
         }
      }

      // place the gates as mode_simulator tiles
      for (auto & gtt : circuitToTiles["circuit"]) {
         unsigned long row {};
         unsigned long column;
         unsigned long placingMoment= gtt["moment"];

         if (gtt["gate"] == "cnot"){
            // row, column coordinates at placement
            unsigned long circuitControlRow= gtt["control"][0];  // json array

            // edge case!
            //             set the column value to place a 'floating' CNOT
            if (placingMoment > s_scene->columnAtRow[circuitControlRow])
               s_scene->columnAtRow[circuitControlRow]= placingMoment;

            unsigned long columnCircuitControl=
                  s_scene->columnAtRow[circuitControlRow];

            unsigned long circuitTargetRow= gtt["target"];
            unsigned long columnCircuitTarget=
                  s_scene->columnAtRow[circuitTargetRow];

            // *** abort read: the count of circuit columns exceeds the columns
            // limit of simulator ***
            if (columnCircuitControl > (implicitRow - 1)
            || columnCircuitTarget > (implicitRow - 1)){
               qDebug() << "process aborted: inserting CNOT will exceed the "
                           "column limits of simulator";
               break ;
            }

            // align the placement columns of CNOT control and its (dummy)
            // target
            if (columnCircuitControl > columnCircuitTarget)
               s_scene->columnAtRow[circuitTargetRow]= columnCircuitControl;
            else if (columnCircuitControl < columnCircuitTarget)
               s_scene->columnAtRow[circuitControlRow]= columnCircuitTarget;

            // set tile-type and upwards/downwards orientation
            if (circuitControlRow > circuitTargetRow){
               // compare with logic for 'operator, CNOT t upwards arrow' in
               // AlgorithmLattice::placeOperator
               row= circuitTargetRow;
               // CNOT t upwards arrow
               openSign= s_scene->p_operators->patterns[6];
            }
            else if (circuitControlRow < circuitTargetRow){
               row= circuitControlRow;
               // CNOT t downwards arrow
               openSign= s_scene->p_operators->patterns[7];
            }

            // place the CNOT
            column= s_scene->columnAtRow[row];
            p_tileType= new SignMeasure(openSign);
            s_scene->prepareOperator(*p_tileType, row, column);

            // advance the column count for row of CNOT (dummy) target
            if (row == circuitControlRow)
               s_scene->columnAtRow[circuitTargetRow] += 1;
            else if (row == circuitTargetRow)
               s_scene->columnAtRow[circuitControlRow] += 1;
         }
         else {
            row= gtt["target"];

            // edge case!
            //             set the column value to place a 'floating' tile
            if (placingMoment > s_scene->columnAtRow[row])
               s_scene->columnAtRow[row]= placingMoment;

            column= s_scene->columnAtRow[row];

            // *** abort read: the count of circuit columns exceeds the columns
            // limit of simulator ***
            if (column > (implicitRow - 1)){
               qDebug() << "process aborted: operator insertion exceeds the "
                           "column limits of simulator";
               break ;
            }
            else {
               if (gtt["gate"] == "h")
                  openSign= s_scene->p_operators->patterns[3];  // 'Hadamard'
               else if (gtt["gate"] == "rx")
                  openSign= s_scene->p_operators->patterns[0];   // 'X-rotation'
               else if (gtt["gate"] == "ry")
                  openSign= s_scene->p_operators->patterns[1];   // 'Y-rotation'
               else if (gtt["gate"] == "rz")
                  openSign= s_scene->p_operators->patterns[2];   // 'Z-rotation'
               else if (gtt["gate"] == "s")
                  openSign= s_scene->p_operators->patterns[4];   // 'S'
               else if (gtt["gate"] == "t")
                  openSign= s_scene->p_operators->patterns[5];   // 'T'
               else if (gtt["gate"] == "x")
                  openSign= s_scene->p_operators->measurements[0];   // 'sigma x'
               else if (gtt["gate"] == "y")
                  openSign= s_scene->p_operators->measurements[1];   // 'sigma y'
               else if (gtt["gate"] == "z")
                  openSign= s_scene->p_operators->measurements[2];   // 'sigma z'
               else
                  continue ;

               p_tileType= new SignMeasure(openSign);
               s_scene->prepareOperator(*p_tileType, row, column);
            }
         }
         s_scene->addItem(p_tileType);

         // iff row has 20 tiles, insert readout tile
         if (column + 1 == latticeDim){
            p_tileType= new SignMeasure(s_scene->ketPlus);
            s_scene->prepareOperator(*p_tileType, row, column + 1);
            s_scene->addItem(p_tileType);

            return ;
         }
      }
   }
   else
      qDebug() << "file is not open";
}

// write instructions, format .txt
void SimulatorView::saveAlgorithm(const QString & wfile
            , const unsigned long (&latticeColumnsAtRow)[latticeDim]) const {
   QFile writefile(wfile);
   // save conditions: write-only, text
   if (!writefile.open(QIODevice::WriteOnly | QIODevice::Text)){
      qDebug() << "file is not open";
      return ;
   }

   QTextStream write(&writefile);

   int arraySize= sizeof(latticeColumnsAtRow) / sizeof(latticeColumnsAtRow[0]);
   int implicitRow {0};
   unsigned int columns= latticeColumnsAtRow[implicitRow];
   QString marker {};

   while (implicitRow < arraySize && columns > 0) {
      for (unsigned int c= 0; c < columns; ++c) {
         QPointF pos= nodeAddress[implicitRow][c];

         QGraphicsItem * p_itemAtColumn= s_scene->itemAt(pos,QTransform());
         if (p_itemAtColumn == nullptr){
            // edge case!
            //             p_itemAtColumn: catch nullptr arising from the
            // required 'operator' being the target qbit of a CNOT at the row
            // immediately adjacent to (implicit)row.  Compare this with
            // similar logic of AlgorithmLattice::placeOperator for context
            QGraphicsItem * p_operatorAtRowMinusOne=
                  s_scene->itemAt(nodeAddress[implicitRow - 1][c], QTransform());
            auto * p_cnotAtRowMinusOne= qgraphicsitem_cast<SignMeasure *>(
                  p_operatorAtRowMinusOne);

            if (p_cnotAtRowMinusOne != nullptr
            && p_cnotAtRowMinusOne->showOperator().startsWith("CNOT t"))
               marker= "CNOT_marker";

            // otherwise,
            //             introduce an x-basis measurement, as per Raussendorf
            // and Briegel (2002) 'Computational Model Underlying The One-Way
            // Quantum Computer'
            if (marker.isEmpty())
               marker= QChar(0x03C3) % " x";
         }
         else {
            auto * p_operatorAtColumn= qgraphicsitem_cast<SignMeasure *>(
                  p_itemAtColumn);
            // edge case!
            //             it appears that QGraphicsScene::itemAt never
            // actually points at NULL but rather the 'returned' nullptr
            // originates with exception-handling as part of a check of memory
            // address.  In effect, this means qgraphicsitem_cast will continue
            // pointing at the last positive match until the next positive
            // match replaces it, thereby creating a phantom operator. This
            // conditional is a specific workaround to the problem and
            // unavoidably repeats logic of the previous if ( == nullptr)
            // conditional.
            if (p_operatorAtColumn->showOperator() == "0" && c > 0)
               marker= QChar(0x03C3) % " x";
            else
               marker= p_operatorAtColumn->showOperator();
         }

         // write: tile type
         write << marker << " "
         // write: row, column position, as x, y coordinates
         << implicitRow << " " << c
         // write: newline
         << "\n";

         marker.clear();
      }
      implicitRow += 1;
      columns= latticeColumnsAtRow[implicitRow];
   }
   auto ioStats= s_scene->p_stats;
   write << "south " << *ioStats->p_perimeterS << "\n";
   write << "east " << *ioStats->p_perimeterE;

   writefile.flush();
   writefile.close();
}


// private
void SimulatorView::latticeFromPatterns(unsigned long placementRow) {
   // derive then render as data
   //    - [last row, last column],
   //    - qbits count,
   //    - count of T-patterns,
   // of the (hypothetical) lattice - 'substrate' - required to resource the
   // algorithm.

   QGraphicsItem * atStatsPos= s_scene->itemAt(statsPos,QTransform());
   auto ioStats= qgraphicsitem_cast<LatticeStats *>(atStatsPos);
/*  TO DO: When latticeFromPatterns follows openAlgorithm, atStatsPos returns NULL
 *qDebug() << "ioStats->p_perimeterS:" << ioStats->p_perimeterS << "; ioStats->p_perimeterE" << ioStats->p_perimeterE << "\n";
 *   // openAlgorithm assigns mStat, nStat but does not update ioStats->p_perimeterS/E
 *   if (mStat > 1){
 *      *ioStats->p_perimeterS= mStat;
 *      mStat= 0;
 *   }
 *qDebug() << "*ioStats->p_perimeterS " << *ioStats->p_perimeterS << "; mStat " << mStat << "\n";
 *   if (nStat > 1){
 *      ioStats->set_perimeterE(nStat);
 *      nStat= 0;
 *   }
 *qDebug() << "*ioStats->p_perimeterE " << *ioStats->p_perimeterE << "; nStat " << nStat;
 */
   // account for |0> placed by AlgorithmLattice constructor or method, addRow
   if (columnLengths[placementRow] == 0)
      columnLengths[placementRow]= 1;

   // adjust for the AlgorithmLattice variable, columnAtRow being the starting
   // position of a pattern
   unsigned long column= s_scene->columnAtRow[placementRow] - 1;

   // get the pattern's position on the lattice
   QPointF pos= nodeAddress[placementRow][column];

   QGraphicsItem * p_itemAtColumn= s_scene->itemAt(pos, QTransform());
   auto * p_operatorAtColumn= qgraphicsitem_cast<SignMeasure *>(
            p_itemAtColumn);
   QString pattern= p_operatorAtColumn->showOperator();

   // reset the (hypothetical) lattice eastern and southern perimeters with the
   // added pattern
   if (pattern == "0"){   // pattern = 'initialise' and the marker of a new row
      if (placementRow > 0)
         mStat += 1;
      columnLengths[placementRow] += 1;
   }
   else if (pattern == "+")   // pattern = 'readout'
      columnLengths[placementRow] += 1;
   else if (pattern.startsWith("CNOT t")){
      columnLengths[placementRow] += 5;
      // align columns
      columnLengths[placementRow + 1]= columnLengths[placementRow];

      if (pattern == "CNOT t" % QChar(0x2191)){   // CNOT target is row - 1
         // does this CNOT qualify as the second of a proxy swap pattern;
         // recall, placementRow determines colSwapProxy1
         if (swapProxy1 && colSwapProxy1 == column - 1)
            swapProxy2= true;
      }
      if (pattern == "CNOT t" % QChar(0x2193)){   // CNOT target is row + 1
         // edge case!
         //            Iff this CNOT pattern is the first in a proxy swap
         // pattern or it is a solitary instance, extend the southern perimeter
         // of the (hypothetical) lattice.
         // Term 3 of the conditional is to prevent two contiguous CNOT
         // downwards arrows (a user running tests on bit flips?) inflating
         // mStat.
         if (swapProxy1 && !swapProxy2 && colSwapProxy1 != column - 1){
            mStat += 2;
            colSwapProxy1= column;   // recall, placementRow determines column
         }
         else if (swapProxy1 && swapProxy2){
            // this CNOT pattern is the third and final in a proxy swap pattern
            swapProxy1= false;
            swapProxy2= false;
         }
      }
   }
   else {   // all other patterns
      columnLengths[placementRow] += 3;
      // increase T-pattern counter
      if (pattern == "T")
         ioStats->countTPatterns += 1;
   }

   // reset nStat?
   if (columnLengths[placementRow] > nStat)
      nStat= columnLengths[placementRow];

   // render statistics of (hypothetical) lattice
   *ioStats->p_perimeterS= mStat;
   *ioStats->p_perimeterE= nStat;
   ioStats->update();
}
