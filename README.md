# NSFinalProject
## To run
1. cd into folder "ns-3.34": ```cd path_to_ns-3.34```
2. Clone this repository: ```git clone https://github.com/mindt102/NSFinalProject.git```
3. Move main.sh from NSFinalProject into ns-3.34: ```mv NSFinalProject/main.sh .```
4. Edit main.sh to change the parameters
5. Run main.sh by ```./main.sh``` or ```bash main.sh```

## To analyze
1. cd into NSFinalProject: ```cd NSFinalProject```
2. To analyze an XML file: ```python3 flowData/file_name```
3. To analyze all XML file after running with 2..30 nodes: ```./analyzeAll.sh``` or ```bash analyzeAll```

## To summarize
1. cd into NSFinalProject: ```cd NSFinalProject```
2. Run the summarize script to see loss flow ratio of each case: ```./summarize.sh``` or ```bash summarize.sh```
