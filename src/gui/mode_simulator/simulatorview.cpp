//
// specify simulator view/scene objects
//

#include "simulatorview.hpp"

#include <QDebug>
#include <QFile>
#include <QScrollBar>
#include <QTextStream>


// public:
SimulatorView::SimulatorView(QWidget * parent)
      : QGraphicsView(parent), s_scene(new AlgorithmLattice(this))
{
   // encompass 21 * 21 tiles
   s_scene->setSceneRect(-760,-500,4150,1580);
   setScene(s_scene);

   const qreal x= s_scene->sceneRect().x();
   const qreal y= s_scene->sceneRect().y();

   auto hbar= new QScrollBar(Qt::Horizontal, this);
   setHorizontalScrollBar(hbar);
   hbar->setSliderPosition((int) x - 25);

   auto vbar= new QScrollBar(Qt::Vertical, this);
   setVerticalScrollBar(vbar);
   vbar->setSliderPosition((int) y - 25);
}

// read instructions, format .txt
void SimulatorView::openAlgorithm(const QString & rfile) {
   QFile loadfile(rfile);
   // read conditions: read-only, text
   if (!loadfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << " file is not open";
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
   int lastRow= 0;
   int savedCol;
   int lastCol= 0;
   QString tileData{inStream.readLine()};

   while (!tileData.isNull()) {
      QStringList tileSpecs= tileData.split(QChar(' '));

      // concatenate operators with white-spacing in name (e.g. 'sigma' 'x')
      if (tileSpecs.length() == 4){
         openSign= tileSpecs.at(0) % " " % tileSpecs.at(1);
         savedRow= tileSpecs.at(2).toInt();
         savedCol= tileSpecs.at(3).toInt();
      }
      else {
         openSign= tileSpecs.at(0);
         savedRow= tileSpecs.at(1).toInt();
         savedCol= tileSpecs.at(2).toInt();
      }

      // accumulate the columns count of each row (inc. dummy CNOT target)
      if (savedCol > lastCol)
         lastCol= savedCol;
      if (lastCol > savedCol && lastRow < savedRow)
         s_scene->columnAtRow[lastRow]= lastCol + 1;
      if (savedRow > lastRow)
         lastRow= savedRow;

      // specify tile but ignore marker for dummy CNOT target (see method,
      // saveAlgorithm below)
      if (openSign != "CNOT_marker") {
         // reproduce tile
         tileType = new SignMeasure(openSign);
         tileType->setPos(nodeAddress[savedRow][savedCol]);

         // update the QComboBox, 'switch rows'
         if (openSign.startsWith("CNOT t")) {
            auto rowValue = QString::number(savedRow + 1);
            s_scene->p_operators->possibleRows->insertItem(savedRow + 1, rowValue);
            // reset 'switch rows' display to the added row
            s_scene->p_operators->possibleRows->setCurrentIndex(savedRow + 1);
         }
         s_scene->addItem(tileType);
      }
      tileData= inStream.readLine();
   }
   s_scene->columnAtRow[savedRow]= savedCol + 1;
   loadfile.close();
}

// read a quantum circuit file, format .json (schemas: 'native', which is
// adapted from ionQ; and Google Cirq, which is reformatted to the native
// schema). See comments of src/layout/io_circuit.cpp.
void SimulatorView::readCircuit(const QString & cjson) {
   // convert QString to utf8 string
   std::string cjson_utf8= cjson.toUtf8().constData();
   std::ifstream json_circuit {cjson_utf8};

   if (json_circuit.is_open()){
      using json= nlohmann::json;

      json parse_circuit= json::parse(json_circuit);   // create json object
      auto cirq_check= parse_circuit.find("cirq_type");

      if (cirq_check != parse_circuit.end()){
         // format of input circuit json: cirq
         json ionq_schema= cirq_to_ionq_schema(parse_circuit);
         etch_circuit= ionq_schema;
      }
         // format of input circuit json: ionQ
      else {
         if (non_adjacent_gate(parse_circuit))
            qDebug() << "process aborted: non-adjacent gate in circuit";

         etch_circuit= parse_circuit;
      }

      unsigned long cluster_state_rows= rows_m(gate_by_address, etch_circuit);
      unsigned long cluster_state_columns= cols_n(gate_by_address
            , etch_circuit);

//      setLattice(cluster_state_rows, cluster_state_columns);
   }
   else
      qDebug() << "That file is not opening";
}

// write instructions, format .txt
void SimulatorView::saveAlgorithm(const QString & wfile
                                , const unsigned long (&latticeColumnsAtRow)[21]) const {
   QFile writefile(wfile);
   // save conditions: write-only, text
   if (!writefile.open(QIODevice::WriteOnly | QIODevice::Text)){
      qDebug() << " file is not open";
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
            // actually points at NULL but rather the nullptr returned by it is
            // from exception-handling of a check of memory address.  In
            // effect, this means qgraphicsitem_cast will continue pointing at
            // the last positive match until the next positive match replaces
            // it, thereby creating a phantom operator. This conditional is a
            // specific workaround to the problem and unavoidably repeats logic
            // of the previous if ( == nullptr) conditional
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
   writefile.flush();
   writefile.close();
}
