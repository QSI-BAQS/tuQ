//
// input JSON-format
//

#ifndef TUQ_IO_CIRCUIT_HPP
#define TUQ_IO_CIRCUIT_HPP

#include "json.hpp"

#include <iostream>
#include <vector>


nlohmann::json cirq_to_ionq_schema(const nlohmann::json &);

#endif //TUQ_IO_CIRCUIT_HPP
