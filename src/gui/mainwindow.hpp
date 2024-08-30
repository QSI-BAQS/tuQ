#ifndef TUQ_MAINWINDOW_HPP
#define TUQ_MAINWINDOW_HPP

#include "mode_compiler/compilerview.hpp"
#include "mode_modeller/graphview.hpp"
#include "gui_helpers.hpp"
#include "mode_simulator/simulatorview.hpp"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
   Q_OBJECT

   enum class tuQ_mode {compiler,modeller,simulator};
   tuQ_mode view_setting {tuQ_mode::modeller};
   tuQ_mode * const p_view_setting= &view_setting;

   GraphSelect * settings {};
   CompilerView * view_compiler {};
   GraphView * view_modeller {};
   SimulatorView * view_simulator {};

   QAction * a_addLattice {};
   QAction * a_compile {};
   QAction * a_openAlgorithm {};
   QAction * a_openGraph {};
   QAction * a_readCircuit {};
   QAction * a_saveAlgorithm {};
   QAction * a_saveGraph {};
   QAction * a_simulate {};

   QMenu * circuitMenu {};
   QMenu * editMenu {};
   QMenu * fileMenu {};
   QMenu * graphMenu {};

   void addLattice();
   void createMenus();
   void dialogOpen(const QString *);
   void dialogSave(const QString *);
   void readCircuitDialog(const QString *);
   void setActions();
   void setView();

private slots:
   void noSession();
   void setCompiler();
   void setModeller();
   void setSimulator();

public:
   explicit MainWindow(QWidget * parent= nullptr);

   const QString * algorithmopenfile {};
   const QString * algorithmsavefile {};
   const QString * graphopenfile {};
   const QString * graphreadcircuit {};
   const QString * graphsavefile {};
};

#endif // TUQ_MAINWINDOW_HPP