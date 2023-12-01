function [stringSize, numChips, dataInitial, stepValues] = agrDataPullInitial(object, numSamples)
    %Read and arrange Intial Data
    %Receive and Split String
    dataRaw = readline(object);
    dataVect = split(dataRaw," ",1);
    %Determine Initial Reading Parameters
    stringSize = (size(dataVect,1)-1)/2;
    numChips = stringSize/3;

    %Convert Data String to Array of Values
    stepValues = zeros(numSamples,stringSize);
    for t=1:numSamples
        stepValues(t,:) = agrDataPullLoop(object, stringSize);
    end

    dataInitial = zeros(1,stringSize);
    for i=1:stringSize
    dataInitial(1,i) = mean(stepValues(1:numSamples,i));
    end


end

