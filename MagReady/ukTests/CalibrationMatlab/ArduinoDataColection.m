clear all;
clc;

%open com port
ComPort = 'COM4';
[s,flag] = setupSerial(ComPort);

%number of data samples to be collected
dataAmount = 10000;

%increase max lim if data lies beyond the boundaries
max_lim = 80000;

%iteration counter
iter=0;

fID = fopen('test3.txt','w');

    hold on;
while iter < dataAmount
    iter=iter+1;
    sprintf("%f",iter)
    
    x=fscanf(s,'%f');
    y=fscanf(s,'%f');
    z=fscanf(s,'%f');
    fprintf(fID,'%.10f\t%.10f\t%.10f\n',x,y,z);
    %if rem(a,200)==0
    
    
   
    plot3(x,y,z,'ro')
    %hold off;
    
    xlim([-max_lim, max_lim])
    ylim([-max_lim, max_lim])
    zlim([-max_lim, max_lim])
    camorbit(0.5,0)
    
    %end

    drawnow
    
end
hold off
fprintf("Ya done")
%if closeSerial() is never reached serial port
%needs to be closed manually by running the function
closeSerial();
fclose(fID);