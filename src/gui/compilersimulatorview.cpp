//
// specify view/scene objects
//

#include "compilersimulatorview.hpp"

#include <QDebug>


// public:
CompilerSimulatorView::CompilerSimulatorView(QWidget * parent)
      : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
   // '... one unit on the scene is represented by one pixel on the screen.'
   // *** ~[121, 121] accessible at this sceneRect ***
   /* FIX: setSceneRect has to be consistent between this and setLattice otherwise
      lattice created in one set of coordinates do not show up in the other set */
   scene->setSceneRect(-2500,-2500,11000,11000);

   setScene(scene);

}



// read a quantum circuit file, format .json (schemas: 'native', which is
// adapted from ionQ; and Google Cirq, which is reformatted to the native
// schema). See comments of src/layout/io_circuit.cpp.
void CompilerSimulatorView::readCircuit(const QString & cjson) {
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
/*
      unsigned long cluster_state_rows= rows_m(gate_by_address, etch_circuit);
      unsigned long cluster_state_columns= cols_n(gate_by_address
            , etch_circuit);

      setLattice(cluster_state_rows, cluster_state_columns);
*/
   }
   else
      qDebug() << "That file is not opening";
}

