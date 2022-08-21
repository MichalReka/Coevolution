import matplotlib.pyplot as plt
import numpy as np
import json
import sys
#sys.path[0] zwraca folder w ktorym jest skrypt, skrypt i json sa w tym samym folderze
with open(sys.path[0]+'//json-test.json') as dataJson:
    noAgents = json.load(dataJson)["BestFitnessesPerSpeciesPerIteration"]
    i=0
    for agentTeam in noAgents:
        i = i + 1
        plt.close()
        plt.bar(range(len(agentTeam)), agentTeam)
        plt.title("Zmiana oceny dla zespołu z wielkością " + str(i))
        plt.ylabel("Najlepsza ocena")
        plt.xticks(color='w')
        plt.savefig('data_test'+str(i)+'.png')
        plt.close()


    #plt.plot(data['bestFitnesses'])

    dataJson.close()
    #os.remove(sys.path[0]+'//tempData.json')
