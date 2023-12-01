close all;
%Initialize Arduino
arduinoObj = serialport("COM5",115200)


%Pull Initial Data
numSamples = 1000; %Minimum = 20 for 20 point rolling average. 100 is maybe useable
[stringSize, numChips, initialMean, startingData] = agrDataPullInitial(arduinoObj, numSamples);