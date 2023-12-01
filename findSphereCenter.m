function [sphereCenter, radius] = findSphereCenter(points)
    % compare to https://www.mathworks.com/matlabcentral/fileexchange/34129-sphere-fit-least-squared
    % points: N-by-3 array of points
    
    % Extract the coordinates of the points
    x = points(:, 1);
    y = points(:, 2);
    z = points(:, 3);
    
    % Create the coefficient matrix A
    A = [2*x, 2*y, 2*z, ones(size(x))];
    
    % Create the right-hand side vector b
    b = x.^2 + y.^2 + z.^2;
    
    % Solve the linear system Ax = b using the least squares method
    coefficients = A\b;
    
    % Extract the sphere center coordinates from the solution
    centerX = coefficients(1);
    centerY = coefficients(2);
    centerZ = coefficients(3);
    
    % Calculate the radius of the sphere
    radius = sqrt(centerX^2 + centerY^2 + centerZ^2 - coefficients(4));
    
    % Create the sphere center vector
    sphereCenter = [centerX, centerY, centerZ];


end