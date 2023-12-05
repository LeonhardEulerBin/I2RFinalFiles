clc; clear all; close all;



data = load("calibrationDataset.mat");

values = data.startingData(10:200,:);

figure(1)
axis equal
title('Spheres of Influence')
xlabel('x');
ylabel('y');
zlabel('z');
hold on
plot3(values(:,1), values(:,2), values(:,3))
plot3(values(:,4), values(:,5), values(:,6))
plot3(values(:,7), values(:,8), values(:,9))
scatter3(0, 0, 0)
hold off

[sphereCenter1, radius1] = findSphereCenter(values(:,1:3));
[sphereCenter2, radius2] = findSphereCenter(values(:,4:6));
[sphereCenter3, radius3] = findSphereCenter(values(:,7:9));

figure(2)
axis equal
title('Spheres of Influence')
xlabel('x');
ylabel('y');
zlabel('z');
hold on
plot3(values(:,1), values(:,2), values(:,3))
plot3(values(:,4), values(:,5), values(:,6))
plot3(values(:,7), values(:,8), values(:,9))
scatter3(0, 0, 0)
scatter3(sphereCenter1(1,1), sphereCenter1(1,2), sphereCenter1(1,3))
scatter3(sphereCenter2(1,1), sphereCenter2(1,2), sphereCenter2(1,3))
scatter3(sphereCenter3(1,1), sphereCenter3(1,2), sphereCenter3(1,3))
hold off



for i=1:size(values,1)
    centeredValues(i,:) = [values(i, 1) - sphereCenter1(1,1), values(i, 2) - sphereCenter1(1,2), values(i, 3) - sphereCenter1(1,3),         values(i, 4) - sphereCenter2(1,1), values(i, 5) - sphereCenter2(1,2), values(i, 6) - sphereCenter2(1,3),        values(i, 7) - sphereCenter3(1,1), values(i, 8) - sphereCenter3(1,2), values(i, 9) - sphereCenter3(1,3)];
end

figure(3)
axis equal
title('Spheres of Influence')
xlabel('x');
ylabel('y');
zlabel('z');
hold on
plot3(centeredValues(:,1), centeredValues(:,2), centeredValues(:,3))
plot3(centeredValues(:,4), centeredValues(:,5), centeredValues(:,6))
plot3(centeredValues(:,7), centeredValues(:,8), centeredValues(:,9))
scatter3(0, 0, 0)

hold off