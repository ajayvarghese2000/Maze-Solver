clear all
clc
ComPort = 'COM4';
[s,flag] = setupSerial(ComPort);



%tw=readOut(s,1000);
figure;
max_lim = 80;
iter=0;
fID = fopen('comp_data.txt','w');
while true
    iter=iter+1;
    
    x=fscanf(s,'%f');
    y=fscanf(s,'%f');
    fprintf(fID,'%f %f\n',x,y);
    %if rem(a,200)==0
    

    hold on;
    xlim([-max_lim max_lim])
    ylim([-max_lim max_lim])
    plot(x,y,'o')
    
    hold off;
    %end
    drawnow
end
fclose(fID);