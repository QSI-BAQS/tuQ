From the Farsi  <bdo dir="rtl"> تور </bdo>  for 'net', t&#363;Q is an interactive tool both for
modelling graph states and running them in a quantum simulator.  To that end t&#363;Q 
empowers the user to simulate cluster-based quantum computing as an alternative 
to circuit-based quantum computing.  Furthermore the user can output its graph 
in openQASM format thereby enabling it to run a graph on any quantum computing 
facility to accept openQASM input.

## Setting up
Installing and building t&#363;Q requires the following environment,
* a *nix distribution; t&#363;Q is not configured to run on either Windows or Mac,
* Qt 5.15,
* Git, version 2.35+
* CMake, version 3.28+.

The user must install,
* nlohmann::json (header library works fine),

for t&#363;Q/src/layout to read it before compiling.

## Configure the 'toQASM' function
The method, toQASM of class Simulatorview requires some customising:
* SimulatorView::toQASM will output the OpenQASM script to a .txt file and at a minimum, the user should set a path to the required output destination as (QFile) variable, filePOST in format '/path/to/file';
* SimulatorView::toQASM default is _not_ to write to an API although the necessary code to do so is part of the method but commented out.  The user should specify the API URL as (std::string) variable, reqStrQASM.  Note, the POST syntax of this method is necessarily generic and thus very simple: it omits such precautions as error-checking or managing bad links; furthermore, it does not cater for an API that requires input encoded in JSON.  The user should modify the code to suit its requirements.

## Citation format
For research citation, kindly reference,
* Bowen, Greg and Devitt, Simon J. 't&#363;Q: a design and modelling tool for cluster-state algorithms' [arXiv:2502.18991](https://arxiv.org/abs/2502.18991)
