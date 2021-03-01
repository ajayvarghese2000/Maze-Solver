function v=proc(data)
%proc

dx=data(1,:)';
dy=data(2,:)';
dz=data(3,:)';
%plot3(dx,dy,dz,'ko')


n=size(dx,1);
D=[dx.*dx, dy.*dy,  dz.*dz, 2.*dy.*dz, 2.*dx.*dz, 2.*dx.*dy, ...
        2.*dx, 2.*dy, 2.*dz, ones(n,1)]';

v=liFit(D*D');

end