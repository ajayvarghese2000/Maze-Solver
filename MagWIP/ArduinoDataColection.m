clear all
clc
ComPort = 'COM4';
[s,flag] = setupSerial(ComPort);

dataAmount = 1500;

%tw=readOut(s,1000);
%figure;
max_lim = 75000;
iter=0;
fID = fopen('test3.txt','w');
while iter < dataAmount
    iter=iter+1;
    sprintf("%f",iter)
    
    x=fscanf(s,'%f');
    y=fscanf(s,'%f');
    z=fscanf(s,'%f');
    fprintf(fID,'%f\t%f\t%f\n',x,y,z);
    %if rem(a,200)==0
    
    
   
    plot3(x,y,z,'ro')
    hold off;
    
    xlim([-max_lim, max_lim])
    ylim([-max_lim, max_lim])
    zlim([-max_lim, max_lim])
    camorbit(0.5,0)
    
    %end
    hold on;
    drawnow
    
end
closeSerial();
fclose(fID);