clear all;
clc;

%open com port
ComPort = 'COM4';
[s,flag] = setupSerialRev2(ComPort,14400);

%number of data samples to be collected
dataAmount = 10000;

%increase max lim if data lies beyond the boundaries
max_lim = 75000;

%iteration counter
iter=0;

fID = fopen('testJ10k.json','w');

fprintf(fID,'[');
while iter < dataAmount
    iter=iter+1;
    sprintf("%f",iter)

    x=fscanf(s,'%c');
    fprintf(fID,x);
    drawnow;
end
fprintf(fID,'{"X":NaN,"Y":NaN,"Z":NaN}]');

%if closeSerial() is never reached serial port
%needs to be closed manually by running the function
closeSerial();
fclose(fID);