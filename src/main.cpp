#include "gui/graphview.hpp"
#include "layout/gates_lattice_set.hpp"
#include "layout/io_circuit.hpp"

#include <fstream>
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
// gui/ main

   QApplication tuq(argc, argv);

   // move and reformat as helper function: begin
   auto * view= new GraphView();
   view->setWindowTitle("tuQ");
   view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   // helper function: end

//   view->set_lattice(15,15);
   view->show();

   return tuq.exec();
// layout/ main
/*
   std::cout << "key in /path/to/json/circuit then, press Enter:" << std::endl;

   std::string icircuit;
   std::cin >> icircuit;
   std::ifstream json_circuit (icircuit);

   if (json_circuit.is_open()){
      using json= nlohmann::json;

      json parse_circuit= json::parse(json_circuit);   // create json object
      auto cirq_check= parse_circuit.find("cirq_type");

      if (cirq_check != parse_circuit.end()){
         // format of input circuit json -> cirq
         json ionq_schema= cirq_to_ionq_schema(parse_circuit);
         etch_circuit= ionq_schema;
      }
      // format of input circuit json -> ionQ
      else {
         if (non_adjacent_gate(parse_circuit)){
            std::cout << "process aborted: non-adjacent gate in circuit.\n" << std::endl;
            return 0;
         }
         etch_circuit= parse_circuit;
      }

      unsigned long cluster_state_rows= rows_m(gate_by_address, etch_circuit);
      unsigned long cluster_state_columns= cols_n(gate_by_address, etch_circuit);

      std::cout << "\nThe input circuit specifies a [" << cluster_state_rows
         << ", " << cluster_state_columns << "] cluster state.\n\n" << std::endl;

      return 0;
   }
   else {
      std::cout << "That file is not opening, it may be,\n  - the file is"
                   " already in use,\n  - the file path is incorrect, or\n  -"
                   " the file is incorrect.\nCheck then, try again.\n" << std::endl;

      return 0;
   }*/
}