function stepValues = agrDataPullLoop(object, stringSize)
    %Read and arrange Intial Data
    %Receive and Split String
    dataRaw = readline(object);
    dataVect = split(dataRaw," ",1);
    %Convert Data String to Array of Values
    i=1;
    for conversionIndex=1:stringSize
        stepValues(1,conversionIndex) = str2double(dataVect(i,1));
        i=i+2;
    end
end


