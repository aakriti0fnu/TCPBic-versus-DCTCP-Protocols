
## Implementation and performance analysis of TCPBic and DcTcp


### How to run the project?

- **Install Ns3**

    https://www.nsnam.org/wiki/Installation

- The experiment code files (exp_1.cc, exp_2.cc, exp_3.cc, exp_4.cc, exp_5.cc) have to be saved in the scratch folder under the path: /ns-allinone-3.32/ns-3.32/scratch


- **To execute and run the code**:

    - save the bash script (tcp.sh) under the path:  /ns-allinone-3.32/ns-3.32
    - run the command:  ./tcp.sh

--- 
**Output**:

- The code execution will generate 5 trace files (.tr) containing the required Measurement Metrics (average flow completion time and throughput) and 5 Animator files (.xml) for the animation (for topology and experiment view)

- The bash script run takes a little longer due to data size (5e7 = 50MB), the wait time is approx. 15 mins for all 5 experiments to complete execution.

    - **Note-1**: The bash script is running way faster when the data size is in the range of 5e1 to 5e6, so it is due to data size that the experiments takes longer time to run


**To run the Animator file (.xml) in Net-Animator**:

- go to the path: /ns-allinone-3.32/netanim-3.108
-  run the command: ./NetAnim
-  open the file from the top-left folder icon and choose the respective experiment files (exp_1.xml, exp_2.xml, exp_3.xml, exp_4.xml, exp_5.xml) to view the experiments.


**To install and run trace files (.tr)**:

- Download the trace metrics software from here: `https://sourceforge.net/projects/tracemetrics/`
- It needs Java, so Java needs to be installed on your machine
- run the command:  `sudo apt install default-jdk`
- unzip the trace metrics folder
- go to the unzipped folder location and run the command:  `java -jar tracemetrics.jar`
- Tracemetrics application will open, choose the output trace metric files (exp_1.tr, exp_2.tr, exp_3.tr, exp_4.tr, exp_5.tr)
- For the respective trace files navigate to the `"Simulation"` tab where `Total Simulation Time` shows the `average flow completion time` and the `"Throughput/Goodput"` tab shows the `throughput values`.

    -  **Note-2**: Node 0 is S1 and Node 1 is S2 in our experiments, so for throughput kindly refer to values of Node 0 and Node 1

    - **Note-3**: The value for throughput obtained is in Bytes-per-second[Bps] and we have converted these values to Mega-Bits-per-second [Mbps] in-order to obtain the required values for the .csv file)
---
**Credits:**
Ashwin Kumar Munniswamy