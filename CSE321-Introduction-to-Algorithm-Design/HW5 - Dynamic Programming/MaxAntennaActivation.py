class Antenna :
    def __init__(self, startPoint, endPoint) :
        self.startPoint = startPoint
        self.endPoint = endPoint
    
def endPointKeyExtractor(antenna) :
    return antenna.endPoint

def maxAntennaActivated(antennas) :
    if (antennas == None) : 
        return 0
    
    sortedAntennas = sorted(antennas, key=endPointKeyExtractor)
    curRangePoint = 0
    antennaNum = 0
    for antenna in sortedAntennas :
        if (antenna.startPoint >= curRangePoint) :
            antennaNum = antennaNum + 1
            curRangePoint = antenna.endPoint + 1
    return antennaNum


def main() :
    ant1 = Antenna(3, 5)
    ant2 = Antenna(7, 10)
    ant3 = Antenna(2, 6)
    ant4 = Antenna(13, 20)
    
    antennas = [ant1, ant2, ant3, ant4]
    print(maxAntennaActivated(antennas))

main()