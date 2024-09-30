//
// assorted helper functions
//

#include "simulator_helpers.hpp"

#include <QStringBuilder>


// public:
LatticeStats::LatticeStats(unsigned long south, unsigned long east)
      : perimeterS(south), perimeterE(east) {}

void LatticeStats::paint(QPainter * painter
      , const QStyleOptionGraphicsItem * option
      , QWidget * widget) {
   Q_UNUSED(option)
   Q_UNUSED(widget)

   painter->setFont(QFont{"Times New Roman", 36});
   painter->setPen(QPen {Qt::black,2});

   QRectF backdrop {-22,-15,875,50};

   QString latticeOutput= "lattice dimensions [" % QString::number(perimeterS)
         % QChar (',') % QString::number(perimeterE) % "]; qubits: "
         % QString::number(perimeterS * perimeterE);
   painter->drawText(backdrop, Qt::AlignLeft,latticeOutput);

   painter->setRenderHint(QPainter::Antialiasing);
}

const QPointF nodeAddress [latticeDim][latticeDim] = {
      { {-725,-475}, {-625,-475}, {-428,-475}, {-231,-475}, {-34,-475}, {163,-475}, {360,-475}, {557,-475}, {754,-475}, {951,-475}, {1148,-475}, {1345,-475}, {1542,-475}, {1739,-475}, {1936,-475}, {2133,-475}, {2330,-475}, {2527,-475}, {2724,-475}, {2921,-475}, {3118,-475} },
      { {-725,-400}, {-625,-400}, {-428,-400}, {-231,-400}, {-34,-400}, {163,-400}, {360,-400}, {557,-400}, {754,-400}, {951,-400}, {1148,-400}, {1345,-400}, {1542,-400}, {1739,-400}, {1936,-400}, {2133,-400}, {2330,-400}, {2527,-400}, {2724,-400}, {2921,-400}, {3118,-400} },
      { {-725,-325}, {-625,-325}, {-428,-325}, {-231,-325}, {-34,-325}, {163,-325}, {360,-325}, {557,-325}, {754,-325}, {951,-325}, {1148,-325}, {1345,-325}, {1542,-325}, {1739,-325}, {1936,-325}, {2133,-325}, {2330,-325}, {2527,-325}, {2724,-325}, {2921,-325}, {3118,-325} },
      { {-725,-250}, {-625,-250}, {-428,-250}, {-231,-250}, {-34,-250}, {163,-250}, {360,-250}, {557,-250}, {754,-250}, {951,-250}, {1148,-250}, {1345,-250}, {1542,-250}, {1739,-250}, {1936,-250}, {2133,-250}, {2330,-250}, {2527,-250}, {2724,-250}, {2921,-250}, {3118,-250} },
      { {-725,-175}, {-625,-175}, {-428,-175}, {-231,-175}, {-34,-175}, {163,-175}, {360,-175}, {557,-175}, {754,-175}, {951,-175}, {1148,-175}, {1345,-175}, {1542,-175}, {1739,-175}, {1936,-175}, {2133,-175}, {2330,-175}, {2527,-175}, {2724,-175}, {2921,-175}, {3118,-175} },
      { {-725,-100}, {-625,-100}, {-428,-100}, {-231,-100}, {-34,-100}, {163,-100}, {360,-100}, {557,-100}, {754,-100}, {951,-100}, {1148,-100}, {1345,-100}, {1542,-100}, {1739,-100}, {1936,-100}, {2133,-100}, {2330,-100}, {2527,-100}, {2724,-100}, {2921,-100}, {3118,-100} },
      { {-725,-25}, {-625,-25}, {-428,-25}, {-231,-25}, {-34,-25}, {163,-25}, {360,-25}, {557,-25}, {754,-25}, {951,-25}, {1148,-25}, {1345,-25}, {1542,-25}, {1739,-25}, {1936,-25}, {2133,-25}, {2330,-25}, {2527,-25}, {2724,-25}, {2921,-25}, {3118,-25} },
      { {-725,50}, {-625,50}, {-428,50}, {-231,50}, {-34,50}, {163,50}, {360,50}, {557,50}, {754,50}, {951,50}, {1148,50}, {1345,50}, {1542,50}, {1739,50}, {1936,50}, {2133,50}, {2330,50}, {2527,50}, {2724,50}, {2921,50}, {3118,50} },
      { {-725,125}, {-625,125}, {-428,125}, {-231,125}, {-34,125}, {163,125}, {360,125}, {557,125}, {754,125}, {951,125}, {1148,125}, {1345,125}, {1542,125}, {1739,125}, {1936,125}, {2133,125}, {2330,125}, {2527,125}, {2724,125}, {2921,125}, {3118,125} },
      { {-725,200}, {-625,200}, {-428,200}, {-231,200}, {-34,200}, {163,200}, {360,200}, {557,200}, {754,200}, {951,200}, {1148,200}, {1345,200}, {1542,200}, {1739,200}, {1936,200}, {2133,200}, {2330,200}, {2527,200}, {2724,200}, {2921,200}, {3118,200} },
      { {-725,275}, {-625,275}, {-428,275}, {-231,275}, {-34,275}, {163,275}, {360,275}, {557,275}, {754,275}, {951,275}, {1148,275}, {1345,275}, {1542,275}, {1739,275}, {1936,275}, {2133,275}, {2330,275}, {2527,275}, {2724,275}, {2921,275}, {3118,275} },
      { {-725,350}, {-625,350}, {-428,350}, {-231,350}, {-34,350}, {163,350}, {360,350}, {557,350}, {754,350}, {951,350}, {1148,350}, {1345,350}, {1542,350}, {1739,350}, {1936,350}, {2133,350}, {2330,350}, {2527,350}, {2724,350}, {2921,350}, {3118,350} },
      { {-725,425}, {-625,425}, {-428,425}, {-231,425}, {-34,425}, {163,425}, {360,425}, {557,425}, {754,425}, {951,425}, {1148,425}, {1345,425}, {1542,425}, {1739,425}, {1936,425}, {2133,425}, {2330,425}, {2527,425}, {2724,425}, {2921,425}, {3118,425} },
      { {-725,500}, {-625,500}, {-428,500}, {-231,500}, {-34,500}, {163,500}, {360,500}, {557,500}, {754,500}, {951,500}, {1148,500}, {1345,500}, {1542,500}, {1739,500}, {1936,500}, {2133,500}, {2330,500}, {2527,500}, {2724,500}, {2921,500}, {3118,500} },
      { {-725,575}, {-625,575}, {-428,575}, {-231,575}, {-34,575}, {163,575}, {360,575}, {557,575}, {754,575}, {951,575}, {1148,575}, {1345,575}, {1542,575}, {1739,575}, {1936,575}, {2133,575}, {2330,575}, {2527,575}, {2724,575}, {2921,575}, {3118,575} },
      { {-725,650}, {-625,650}, {-428,650}, {-231,650}, {-34,650}, {163,650}, {360,650}, {557,650}, {754,650}, {951,650}, {1148,650}, {1345,650}, {1542,650}, {1739,650}, {1936,650}, {2133,650}, {2330,650}, {2527,650}, {2724,650}, {2921,650}, {3118,650} },
      { {-725,725}, {-625,725}, {-428,725}, {-231,725}, {-34,725}, {163,725}, {360,725}, {557,725}, {754,725}, {951,725}, {1148,725}, {1345,725}, {1542,725}, {1739,725}, {1936,725}, {2133,725}, {2330,725}, {2527,725}, {2724,725}, {2921,725}, {3118,725} },
      { {-725,800}, {-625,800}, {-428,800}, {-231,800}, {-34,800}, {163,800}, {360,800}, {557,800}, {754,800}, {951,800}, {1148,800}, {1345,800}, {1542,800}, {1739,800}, {1936,800}, {2133,800}, {2330,800}, {2527,800}, {2724,800}, {2921,800}, {3118,800} },
      { {-725,875}, {-625,875}, {-428,875}, {-231,875}, {-34,875}, {163,875}, {360,875}, {557,875}, {754,875}, {951,875}, {1148,875}, {1345,875}, {1542,875}, {1739,875}, {1936,875}, {2133,875}, {2330,875}, {2527,875}, {2724,875}, {2921,875}, {3118,875} },
      { {-725,950}, {-625,950}, {-428,950}, {-231,950}, {-34,950}, {163,950}, {360,950}, {557,950}, {754,950}, {951,950}, {1148,950}, {1345,950}, {1542,950}, {1739,950}, {1936,950}, {2133,950}, {2330,950}, {2527,950}, {2724,950}, {2921,950}, {3118,950} },
      { {-725,1025}, {-625,1025}, {-428,1025}, {-231,1025}, {-34,1025}, {163,1025}, {360,1025}, {557,1025}, {754,1025}, {951,1025}, {1148,1025}, {1345,1025}, {1542,1025}, {1739,1025}, {1936,1025}, {2133,1025}, {2330,1025}, {2527,1025}, {2724,1025}, {2921,1025}, {3118,1025} }
};

//public:
QPushButton * h_createOperatorButton(const QString & marker) {
   auto * clusterOperator= new QPushButton;
   // button text and formatting
   clusterOperator->setStyleSheet("QPushButton { color: blue; }");

   QFont buttonFont= clusterOperator->font();
   buttonFont.setFamily("Times New Roman");
   buttonFont.setPointSize(18);

   clusterOperator->setFont(buttonFont);
   clusterOperator->setText(marker);

   return clusterOperator;
}