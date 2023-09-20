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
/*
const char control_cnot[6] {'X','Y','Y','Y','Y','Y'};
const char target_cnot[6] {'X','X','X','Y','X','X'};

const char h[4] {'X','Y','Y','Y'};   // Hadamard, Clifford
const char rot[4] {'X','N','N','N'};   // 'arbitrary rotation', non-Clifford
const char s[4] {'X','X','Y','X'};   // 'pi/2 phase gate', Clifford
   *** tuQ: see Raussendorf et al. (2003) figures 10, 12 for Swap gate
const char t[4] {'X','X','N','X'};   // ** PROXY PATTERN ** z-rotation, non-Clifford

*/

// function prototypes
unsigned long cols_n(std::vector<Gate_SE_SW> &, const nlohmann::json &);
bool non_adjacent_gate(const nlohmann::json &);   // drop for tuQ?
unsigned long rows_m(std::vector<Gate_SE_SW> &, const nlohmann::json &);

#endif //TUQ_GATES_LATTICE_SET_HPP
