//
// specify a cluster state by measurement dimensions
//

#ifndef TUQ_GATES_LATTICE_SET_HPP
#define TUQ_GATES_LATTICE_SET_HPP

#include "json.hpp"

#include <vector>


// basic_json: iterable container of input circuit
static nlohmann::json etch_circuit;

// triple: gate and its SE, SW coordinates
struct Gate_SE_SW {
   std::string gate;
   unsigned long se_row {0};
   unsigned long sw_column {0};
};

// resource cluster references
static std::vector<Gate_SE_SW> gate_by_address;

unsigned long cols_n(std::vector<Gate_SE_SW> &, const nlohmann::json &);
bool non_adjacent_gate(const nlohmann::json &);
unsigned long rows_m(std::vector<Gate_SE_SW> &, const nlohmann::json &);

#endif //TUQ_GATES_LATTICE_SET_HPP
