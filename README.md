
# Covid-19-tracker-simulator

## 1. Authors

[Carlos García](https://github.com/cxrlos)\
[Victor Coeto](https://github.com/vcoetoG)\
[Yann Le Lorier](https://github.com/yannlelorier)

## 2. Context

The COVID-19 pandemic is rapidly spreading through the world. With this in view, we wanted to create a program using graph theory to study how a disease spreads through a population, using the classic Gillespie algorithm found [here](https://link.springer.com/content/pdf/bbm%3A978-3-319-50806-1%2F1.pdf).

## 3. Project Description

### 3. 1 The Gillespie algorithm

The Gillespie algorithm is a methodology that aims to track Markovian processes where objects change status. In this case, we wish to use this algorithm in a given starting graph, see the end graph, and the changes over time. It is based on an epidemics model called SIR (Susceptible, Infected, Recovered).

#### 3.1.1 Input/Output

- **Input** Network graph G, a transmission rate &tau;, a recovery rate &gamma;, a set of index node(s) of ```initial_infections```, maximum time t<sub>max</sub>
- **Output** Lists time, S, I and R giving number in each state at each time, *i.e.* S := |G|-len(```infected_nodes```), I:=len(```infected_nodes```) and R:=len( ```infected_nodes```)

#### 3.1.2 Variables

- The infected nodes are updated. In the very first iteration, the infected nodes are the ```initial_infections```\
- The ```at_risk_nodes``` are updated as the nodes which are direct neighbors of infected nodes\
- The infection rate in the at_risk_nodes is updated as &tau;*```len(infected_neighbors)```\
- The ```total_infection_rate``` is updated as the sum of all the infection rates in the ```at_risk_nodes``` group\
- The ```total_recovery_rate``` is updated as &gamma;*```len(infected_nodes)```
- ```total_rate``` is updated as the ```total_transmission_rate + total_recovery_rate```
- ```time``` is updated as the exponential variation taking as argument the ```total_rate```

#### 3.1.3 explanation of an iteration

The main loop iterating, until ```time``` &lt; t<sub>max</sub> and the ```total_rate``` &lt; 0

- r is updated as a uniform random distribution taking 0 and ```total_rate```, then

    - if r &lt; ```total_recovery_rate``` then remove one node from the infected nodes, and reduce infection rate
    - if not, then add one node in the ```at_risk_nodes``` to put it in the ```infected_nodes``` group, and update its neghbors to ```at_risk_nodes``` group.
- update ```times```, S, I and R
- update total recovery rate, total infection rate, and total rate
- ```time``` is updated as ```time + exponential_variate(total rate)```

### 3.2 Execution of the project

The following steps will be taken:

- [ ] From a given file, the initial graph is read
- [ ] The iteration of the algorithm is made and logged into a buffer to write into a pipe in order to create an epidemic_log file
- [ ] Various files can be loaded into the program at the same time using threads
- [ ] An output graph is dumped, to see the final result at a given time.

### 3.3 Progress

![progress](https://progress-bar.dev/0/ "progress")

## 4. Topics

1. **System Calls** or **pipes**
   - To log the information into a file
2. **Threads**
   - Graph creation
3. **Inter Process Communication**
    - Client/Server communication
4. **Dynamic Memory**
    - To store the graph information in an array

## 5. Use Cases

We wish to see different snapshots at different periods of time, letting the algorithm take its course up until a certain point in time.

## 6. Dependencies

- C++ environment (gpp 2.0+)
- [SFML library](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
- cmake (3.1 minimum)

## 7. Running the program

```sh
mkdir build && cd build
cmake ..
make
./covid-sim
```

## References

- [Stochastic simulations of Epidemics](https://link.springer.com/content/pdf/bbm%3A978-3-319-50806-1%2F1.pdf)
