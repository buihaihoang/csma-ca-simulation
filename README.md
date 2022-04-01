# NSFinalProject
## To run
1. cd into folder "ns-3.34": ```cd path_to_ns-3.34```
2. Clone this repository: ```git clone https://github.com/mindt102/NSFinalProject.git```
3. Move main.sh from NSFinalProject into ns-3.34: ```mv NSFinalProject/main.sh .```
4. Edit main.sh to change the parameters
5. Run main.sh by ```./main.sh``` or ```bash main.sh```

## To analyze
1. cd into NSFinalProject: ```cd NSFinalProject```
2. To analyze an XML file: ```python3 analyze.py flowData/path_to_file```
3. To analyze all XML file after running with 2..30 nodes: ```./analyzeAll.sh configuration``` or ```bash analyzeAll.sh configuration```

## To summarize
1. cd into NSFinalProject: ```cd NSFinalProject```
2. Run the summarize script to see loss flow ratio of each case: ```./summarize.sh``` or ```bash summarize.sh```

## To plot the summarized data
1. cd into NSFinalProject: ```cd NSFinalProject```
2. Run the python script ```python3 plot.py path_to_summary_file```
