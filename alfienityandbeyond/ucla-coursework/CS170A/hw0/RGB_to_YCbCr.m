function [Y_uint8 Cb_uint8 Cr_uint8] = YCbCr(Rval, Gval, Bval)
    MAXJSAMPLE = 255;
    CENTERJSAMPLE = 128;

    R = double(Rval);
    G = double(Gval);
    B = double(Bval);
    if (max(max([R G B])) <= 1.0)
       R = R * MAXJSAMPLE;
       G = G * MAXJSAMPLE;
       B = B * MAXJSAMPLE;
    end;

    Y  =  0.29900 * R + 0.58700 * G + 0.11400 * B;
    Cb = -0.16874 * R - 0.33126 * G + 0.50000 * B  + CENTERJSAMPLE;
    Cr =  0.50000 * R - 0.41869 * G - 0.08131 * B  + CENTERJSAMPLE;

    Y_uint8  = uint8( Y );
    Cb_uint8 = uint8( Cb );
    Cr_uint8 = uint8( Cr );
