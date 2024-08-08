#ifndef TUQ_SIMULATOR_HELPERS_HPP
#define TUQ_SIMULATOR_HELPERS_HPP

// {x,y}
QPointF nodeAddress [21][21] {
   { {-725,-475}, {-528,-475}, {-331,-475}, {-134,-475}, {63,-475}, {260,-475}, {457,-475}, {654,-475}, {851,-475}, {1048,-475}, {1245,-475}, {1442,-475}, {1639,-475}, {1836,-475}, {2033,-475}, {2230,-475}, {2427,-475}, {2624,-475}, {2821,-475}, {3018,-475}, {3215,-475} },
   { {-725,-400}, {-528,-400}, {-331,-400}, {-134,-400}, {63,-400}, {260,-400}, {457,-400}, {654,-400}, {851,-400}, {1048,-400}, {1245,-400}, {1442,-400}, {1639,-400}, {1836,-400}, {2033,-400}, {2230,-400}, {2427,-400}, {2624,-400}, {2821,-400}, {3018,-400}, {3215,-400} },
   { {-725,-325}, {-528,-325}, {-331,-325}, {-134,-325}, {63,-325}, {260,-325}, {457,-325}, {654,-325}, {851,-325}, {1048,-325}, {1245,-325}, {1442,-325}, {1639,-325}, {1836,-325}, {2033,-325}, {2230,-325}, {2427,-325}, {2624,-325}, {2821,-325}, {3018,-325}, {3215,-325} },
   { {-725,-250}, {-528,-250}, {-331,-250}, {-134,-250}, {63,-250}, {260,-250}, {457,-250}, {654,-250}, {851,-250}, {1048,-250}, {1245,-250}, {1442,-250}, {1639,-250}, {1836,-250}, {2033,-250}, {2230,-250}, {2427,-250}, {2624,-250}, {2821,-250}, {3018,-250}, {3215,-250} },
   { {-725,-175}, {-528,-175}, {-331,-175}, {-134,-175}, {63,-175}, {260,-175}, {457,-175}, {654,-175}, {851,-175}, {1048,-175}, {1245,-175}, {1442,-175}, {1639,-175}, {1836,-175}, {2033,-175}, {2230,-175}, {2427,-175}, {2624,-175}, {2821,-175}, {3018,-175}, {3215,-175} },
   { {-725,-100}, {-528,-100}, {-331,-100}, {-134,-100}, {63,-100}, {260,-100}, {457,-100}, {654,-100}, {851,-100}, {1048,-100}, {1245,-100}, {1442,-100}, {1639,-100}, {1836,-100}, {2033,-100}, {2230,-100}, {2427,-100}, {2624,-100}, {2821,-100}, {3018,-100}, {3215,-100} },
   { {-725,-25}, {-528,-25}, {-331,-25}, {-134,-25}, {63,-25}, {260,-25}, {457,-25}, {654,-25}, {851,-25}, {1048,-25}, {1245,-25}, {1442,-25}, {1639,-25}, {1836,-25}, {2033,-25}, {2230,-25}, {2427,-25}, {2624,-25}, {2821,-25}, {3018,-25},  {3215,-25} },
   { {-725,50}, {-528,50}, {-331,50}, {-134,50}, {63,50}, {260,50}, {457,50}, {654,50}, {851,50}, {1048,50}, {1245,50}, {1442,50}, {1639,50}, {1836,50}, {2033,50}, {2230,50}, {2427,50}, {2624,50}, {2821,50}, {3018,50}, {3215,50} },
   { {-725,125}, {-528,125}, {-331,125}, {-134,125}, {63,125}, {260,125}, {457,125}, {654,125}, {851,125}, {1048,125}, {1245,125}, {1442,125}, {1639,125}, {1836,125}, {2033,125}, {2230,125}, {2427,125}, {2624,125}, {2821,125}, {3018,125}, {3215,125} },
   { {-725,200}, {-528,200}, {-331,200}, {-134,200}, {63,200}, {260,200}, {457,200}, {654,200}, {851,200}, {1048,200}, {1245,200}, {1442,200}, {1639,200}, {1836,200}, {2033,200}, {2230,200}, {2427,200}, {2624,200}, {2821,200}, {3018,200}, {3215,200} },
   { {-725,275}, {-528,275}, {-331,275}, {-134,275}, {63,275}, {260,275}, {457,275}, {654,275}, {851,275}, {1048,275}, {1245,275}, {1442,275}, {1639,275}, {1836,275}, {2033,275}, {2230,275}, {2427,275}, {2624,275}, {2821,275}, {3018,275}, {3215,275} },
   { {-725,350}, {-528,350}, {-331,350}, {-134,350}, {63,350}, {260,350}, {457,350}, {654,350}, {851,350}, {1048,350}, {1245,350}, {1442,350}, {1639,350}, {1836,350}, {2033,350}, {2230,350}, {2427,350}, {2624,350}, {2821,350}, {3018,350}, {3215,350} },
   { {-725,425}, {-528,425}, {-331,425}, {-134,425}, {63,425}, {260,425}, {457,425}, {654,425}, {851,425}, {1048,425}, {1245,425}, {1442,425}, {1639,425}, {1836,425}, {2033,425}, {2230,425}, {2427,425}, {2624,425}, {2821,425}, {3018,425}, {3215,425} },
   { {-725,500}, {-528,500}, {-331,500}, {-134,500}, {63,500}, {260,500}, {457,500}, {654,500}, {851,500}, {1048,500}, {1245,500}, {1442,500}, {1639,500}, {1836,500}, {2033,500}, {2230,500}, {2427,500}, {2624,500}, {2821,500}, {3018,500}, {3215,500} },
   { {-725,575}, {-528,575}, {-331,575}, {-134,575}, {63,575}, {260,575}, {457,575}, {654,575}, {851,575}, {1048,575}, {1245,575}, {1442,575}, {1639,575}, {1836,575}, {2033,575}, {2230,575}, {2427,575}, {2624,575}, {2821,575}, {3018,575}, {3215,575} },
   { {-725,650}, {-528,650}, {-331,650}, {-134,650}, {63,650}, {260,650}, {457,650}, {654,650}, {851,650}, {1048,650}, {1245,650}, {1442,650}, {1639,650}, {1836,650}, {2033,650}, {2230,650}, {2427,650}, {2624,650}, {2821,650}, {3018,650}, {3215,650} },
   { {-725,725}, {-528,725}, {-331,725}, {-134,725}, {63,725}, {260,725}, {457,725}, {654,725}, {851,725}, {1048,725}, {1245,725}, {1442,725}, {1639,725}, {1836,725}, {2033,725}, {2230,725}, {2427,725}, {2624,725}, {2821,725}, {3018,725}, {3215,725} },
   { {-725,800}, {-528,800}, {-331,800}, {-134,800}, {63,800}, {260,800}, {457,800}, {654,800}, {851,800}, {1048,800}, {1245,800}, {1442,800}, {1639,800}, {1836,800}, {2033,800}, {2230,800}, {2427,800}, {2624,800}, {2821,800}, {3018,800}, {3215,800} },
   { {-725,875}, {-528,875}, {-331,875}, {-134,875}, {63,875}, {260,875}, {457,875}, {654,875}, {851,875}, {1048,875}, {1245,875}, {1442,875}, {1639,875}, {1836,875}, {2033,875}, {2230,875}, {2427,875}, {2624,875}, {2821,875}, {3018,875}, {3215,875} },
   { {-725,950}, {-528,950}, {-331,950}, {-134,950}, {63,950}, {260,950}, {457,950}, {654,950}, {851,950}, {1048,950}, {1245,950}, {1442,950}, {1639,950}, {1836,950}, {2033,950}, {2230,950}, {2427,950}, {2624,950}, {2821,950}, {3018,950}, {3215,950} },
   { {-725,1025}, {-528,1025}, {-331,1025}, {-134,1025}, {63,1025}, {260,1025}, {457,1025}, {654,1025}, {851,1025}, {1048,1025}, {1245,1025}, {1442,1025}, {1639,1025}, {1836,1025}, {2033,1025}, {2230,1025}, {2427,1025}, {2624,1025}, {2821,1025}, {3018,1025}, {3215,1025} }
};

// OperatorPalette::h_createOperatorButton ??

#endif //TUQ_SIMULATOR_HELPERS_HPP

