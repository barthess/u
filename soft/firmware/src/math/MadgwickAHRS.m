classdef MadgwickAHRS < handle
%MADGWICKAHRS Implementation of Madgwick's IMU and AHRS algorithms
%
%   For more information see:
%   http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
%
%   Date          Author          Notes
%   28/09/2011    SOH Madgwick    Initial release

    %% Public properties
  properties (Access = public)
    dT = 1/256;
    Q = [1 0 0 0].';     % output quaternion describing the Earth relative to the sensor
	Beta = 0;               	    % algorithm gain
    Zeta = 0;               	    % algorithm gain
    Ab = [0 0 0].';               % accel bias
    Wb = [0 0 0].';               % gyro bias
  end

      
  methods (Access = private)       
    function obj = UpdateMARG(obj, Gyroscope, Accelerometer, Magnetometer)
      q = obj.Q; % short name local variable for readability
      wb = obj.Wb;
      % Normalise accelerometer and magnetometer measurement
      if (norm(Accelerometer) == 0) || (norm(Magnetometer) == 0)
        return;
      end	% handle NaN
      Accelerometer = (Accelerometer) / norm(Accelerometer);	% normalise magnitude
      Magnetometer = Magnetometer / norm(Magnetometer);	% normalise magnitude
      
      % Reference direction of Earth's magnetic field
      h = quatmult(q, quatmult([0 Magnetometer].', quatcon(q)));
      m_n = h(2);
      m_u = h(3);
      m_e = h(4);
      
      b = [norm([m_n m_e]) m_u 0];
     
	  % Reference direction of Earth's G feild
      d = [0 1 0];
      %Gradient decent algorithm corrective step
      F = [obj.F_m(q,d,Accelerometer);
           obj.F_m(q,b,Magnetometer)];  
      J = [obj.J_m(q,d);
           obj.J_m(q,b)];
      step = J'*F;         
      step = step / norm(step);	% normalise step magnitude
      Gyroscope = Gyroscope-wb.';
      % Compute rate of change of quaternion
      qDot_w = 0.5*quatmult(q, [0 Gyroscope(1) Gyroscope(2) Gyroscope(3)].');
      qDot = qDot_w - obj.Beta * step;
	  obj.Q_w = q_w/norm(q_w);
      % Integrate to yield quaternion
      q = q + qDot*obj.dT;
      obj.Q = q/norm(q); % normalise quaternion
      
      delta_wb = 2*obj.Zeta*obj.dT*quatmult(quatcon(q), step);
      obj.Wb = wb+delta_wb(2:4);
    end
        
  end
  methods (Static)
    function Jx = J_m(q,d)
      dx = d(1);
      dy = d(2);
      dz = d(3);
      q1 = q(1);
      q2 = q(2);
      q3 = q(3);
      q4 = q(4);

      Jx = [2*dy*q4 - 2*dz*q3,           2*dy*q3 + 2*dz*q4, 2*dy*q2 - 4*dx*q3 - 2*dz*q1, 2*dy*q1 - 4*dx*q4 + 2*dz*q2;
            2*dz*q2 - 2*dx*q4, 2*dx*q3 - 4*dy*q2 + 2*dz*q1,           2*dx*q2 + 2*dz*q4, 2*dz*q3 - 4*dy*q4 - 2*dx*q1;
            2*dx*q3 - 2*dy*q2, 2*dx*q4 - 2*dy*q1 - 4*dz*q2, 2*dx*q1 + 2*dy*q4 - 4*dz*q3,           2*dx*q2 + 2*dy*q3];
    end
    function Fx = F_m(q,d,s)
      dx = d(1);
      dy = d(2);
      dz = d(3);
      q1 = q(1);
      q2 = q(2);
      q3 = q(3);
      q4 = q(4);
      sx = s(1);
      sy = s(2);
      sz = s(3);
      
      Fx = [2*dx*(0.5-q3^2-q4^2) + 2*dy*(q1*q4+q2*q3)   + 2*dz*(q2*q4-q1*q3)   - sx;
            2*dx*(q2*q3-q1*q4)   + 2*dy*(0.5-q2^2-q4^2) + 2*dz*(q1*q2+q3*q4)   - sy;
            2*dx*(q1*q3+q2*q4)   + 2*dy*(q3*q4-q1*q2)   + 2*dz*(0.5-q2^2-q3^2) - sz];
    end 
  end
end
