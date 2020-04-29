
# Covid-19-tracker-USA-Mex

## Authors

[Carlos García](https://github.com/cxrlos)\
[Victor Coeto](https://github.com/vcoetoG)\
[Yann Le Lorier](https://github.com/yannlelorier)

## Context

The COVID-19 pandemic is rapidly spreading through the world. Which raises the need to make fast decisions with the help of programs able to represent useful information, in real time. Information is being constantly updated, and in some cases, the data from past cases needs to be updated:

### [CONACYT Website](https://datos.covid-19.conacyt.mx/#DOView) information available

| Municipio        | Población |     fecha_1        | ...  |       fecha_n      |
|:----------------:|:---------:|:------------------:|:----:|:------------------:|
| Zinacantán       | 150000    |   c<sub>11</sub>   | ...  |   c<sub>n1</sub>   |
| Chenalhó         | 160000    |   c<sub>12</sub>   | ...  |   c<sub>n2</sub>   |
| Acteal           | 100000    |   c<sub>13</sub>   | ...  |   c<sub>n3</sub>   |
| San Juan Chamula | 200000    |   c<sub>14</sub>   | ...  |   c<sub>n4</sub>   |
|...|

Where C<sub>ij</sub> is the number of cases (confirmed, suspicious, or deaths) on the i-th day for i in {1, 2, 3, ..., n}, and the j-th municipality in {1, 2, 3, ..., m}\
We are proposing a solution to pull the information from mexican authorities, such as INEGI, the Dirección General de Epidemiología, or the new CONACYT website, and even the Centers for Disease and Control (CDC), and display data in a graphical way using a client/server architecture.

## Project Description

The CDC is part of several organizations that uses the Socrata Open Data APIs, a project created to pull information from governmental institutions, NGOs from around the world.\
After reading the documentation on the APIs available to pull information from the CDC, we realized there is no support to use the API with the C or C++ languages, But there exists support for Python.

Nonetheless, we plan to follow these steps

- [ ] Pull the information using the ```sodapy``` module available from the [Socrata documentation](https://dev.socrata.com/)
- [ ] Create a method that automatically downloads the INEGI's CSV data file and that passes the values to the desired format.
- [ ] Generate a function that compares both the INEGI and CDC values.
- [ ] Develop a function that calculates the difference between the insertion-day values and the further updates.
- [ ] Produce graphs based on the downloaded data and the previously generated values.
- [ ] Transition to a Client/Server architecture.

Using a Python driver that we can use to take information from the CDC, we will have to recalculate the information provided by the website, because according to the sub-secretary of Health López-Gatell, the number of COVID-19 cases provided for a previous day may or may not change. So each time that the client requests information, all of the registries in the INEGI table of cases will have to be re-processed.\
Since the data provided can be changed, we are going to make a local file which will store the past CSV and when the server starts up we will compare it with the new CSV so we know how trust worthy the information is, we will have a counter that tells us how many values have been changed and based on that we can know how trust worthy the information is.\
The server has mainly two functions: load the API for python or load the automatic data downloader for the CONACYT.

### Progress

![progress](https://progress-bar.dev/0/ "progress")

## Topics

1. **System Calls** or **pipes**
   - C++ script call for python data extraction
2. **Threads**
   - Graph production.
3. **Inter Process Communication**
    - Client/Server communication
4. **Dynamic Memory**
    - To store the csv information in a matrix

## Use Cases

Due to the uncertain nature of the disease, it's common to experience several unreported cases. After the meticulous revision of these cases, the respective organizations update the data which leads to variations in the data obtained some days before. In the project, we will develop a function that will calculate these as a tool to help the user understand the average latency from the initial to the final values.

## Dependencies

- C++ environment (gpp 2.0+)
- Python 3 with the following libraries: [```selenium```](https://github.com/SeleniumHQ/selenium) and [```sodapy```](https://pypi.org/project/sodapy/), and [```pandas```](https://pandas.pydata.org)

## References

- [Socrata Open APIs](https://dev.socrata.com/)
- [CDC Dataset on the novel Coronavirus](https://www.cdc.gov/coronavirus/2019-ncov/cases-updates/cases-in-us.html)
- [CONACYT - COVID-19](https://datos.covid-19.conacyt.mx/#DOView)
