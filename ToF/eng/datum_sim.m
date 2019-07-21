classdef datum_sim < handle
    properties
        name
        amplitude
        period % in samples
        phase % also in samples
        offset
        noise
        n
    end
    methods
        function obj = datum_sim(name,amplitude,period,phase,offset,noise)
            obj.name = name;
            obj.amplitude = amplitude;
            obj.period = period;
            obj.phase = phase;
            obj.offset = offset;
            obj.noise = noise;
            obj.n = 0;
        end
        function val = sample(obj)
            val = obj.amplitude * sin((obj.n+obj.phase) * 2*pi/obj.period) + ...
                obj.offset + obj.noise * randn(1);
            obj.n = obj.n + 1;
        end
    end
end