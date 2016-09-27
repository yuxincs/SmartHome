`timescale 1ns / 1ps

module SEG7 (
    output reg [7:0] oSEG,
    input [2:0] iDIG
    );

    always@(iDIG) 
    begin
        case(iDIG)
            3'd0: oSEG = 8'b11000000;
            3'd1: oSEG = 8'b11111001;  
            3'd2: oSEG = 8'b10100100;  
            3'd3: oSEG = 8'b10110000;  
            3'd4: oSEG = 8'b10011001; 
            3'd5: oSEG = 8'b10010010; 
            3'd6: oSEG = 8'b10000010;  
            3'd7: oSEG = 8'b11111000; 
            4'd8: oSEG = 8'b10000000;  
            4'd9: oSEG = 8'b10010000;
            //If error occurs , illuminate none leds.
            default: oSEG = 8'b11111111;  
        endcase    
    end     
endmodule

