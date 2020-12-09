#include "AvgCalc.h"
#include "polymorphismLogicClassesUtilities.h"

int main()
{   
    // input wires
    Wire    clk('X', 0);
    Wire    start('X', 0);
    WireV   data("XXXXXXXX", 0, 8);
    
    // output wires
    WireV   avg("XXXXXXXX", 0, 8);
    Wire    rdy('X', 0);

    // instantiate the average calculator
    AvgCalc *avgCalc = new AvgCalc(start, clk, data, avg, rdy);

    // test case 1 (all bytes are "00000000")
    // =================================================================
    cout << "Test case 1 begins...\n";
    cout << "=============================================\n";
    cout << "Expected avg = 00000000\n";
    start.put('1', 1);
    clk.put('P', 2);
    data.put("00000000", 3);
    avgCalc->evl();

    start.put('N', 4);          // negedge start
    data.put("00000000", 5);
    clk.put('1', 6);
    avgCalc->evl();

    cout << "\nNegedge of start was received...\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);;

    start.put('0', 7);          
    data.put("00000000", 8);    // byte 0
    clk.put('P', 9);            // posedge clk
    avgCalc->evl();

    start.put('0', 10);
    data.put("00000000", 11);    // byte 1
    clk.put('P', 12);            // posedge clk
    avgCalc->evl();

    start.put('0', 13);
    data.put("00000000", 14);    // byte 2
    clk.put('P', 15);            // posedge clk
    avgCalc->evl();

    start.put('0', 16);
    data.put("00000000", 17);    // byte 3
    clk.put('P', 18);            // posedge clk
    avgCalc->evl();

    start.put('0', 19);
    data.put("00000000", 20);    // byte 4
    clk.put('P', 21);            // posedge clk
    avgCalc->evl();

    start.put('0', 22);
    data.put("00000000", 23);    // byte 5
    clk.put('P', 24);            // posedge clk
    avgCalc->evl();

    start.put('0', 25);
    data.put("00000000", 26);   // byte 6
    clk.put('P', 27);           // posedge clk
    avgCalc->evl();

    start.put('0', 28);
    data.put("00000000", 29);   // byte 7
    clk.put('P', 30);           // posedge clk
    avgCalc->evl();

    // display the result
    cout << "\nResults:\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);
    cout << "Test case 1 ends...\n\n";

    // test case 2 (all bytes are "11111111")
    // =================================================================
    cout << "Test case 2 begins...\n";
    cout << "=============================================\n";
    cout << "Expected avg = 11111111\n";
    start.put('1', 30);
    clk.put('P', 31);
    data.put("00000000", 32);
    avgCalc->evl();

    start.put('N', 33);          // negedge start
    data.put("00000000", 34);
    clk.put('1', 35);
    avgCalc->evl();

    cout << "\nNegedge of start was received...\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);;

    start.put('0', 36);
    data.put("11111111", 37);    // byte 0
    clk.put('P', 38);            // posedge clk
    avgCalc->evl();

    start.put('0', 39);
    data.put("11111111", 40);    // byte 1
    clk.put('P', 41);            // posedge clk
    avgCalc->evl();

    start.put('0', 42);
    data.put("11111111", 43);    // byte 2
    clk.put('P', 44);            // posedge clk
    avgCalc->evl();

    start.put('0', 45);
    data.put("11111111", 46);    // byte 3
    clk.put('P', 47);            // posedge clk
    avgCalc->evl();

    start.put('0', 48);
    data.put("11111111", 49);    // byte 4
    clk.put('P', 50);            // posedge clk
    avgCalc->evl();

    start.put('0', 51);
    data.put("11111111", 52);    // byte 5
    clk.put('P', 53);            // posedge clk
    avgCalc->evl();

    start.put('0', 54);
    data.put("11111111", 55);    // byte 6
    clk.put('P', 56);            // posedge clk
    avgCalc->evl();

    start.put('0', 57);
    data.put("11111111", 58);    // byte 7
    clk.put('P', 59);            // posedge clk
    avgCalc->evl();

    // display the result
    cout << "\nResults:\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);
    cout << "Test case 2 ends...\n\n";

    // test case 3 (bytes = 00000001, 00000011, 00000111, ..., 11111111)
    // =================================================================
    cout << "Test case 3 begins...\n";
    cout << "=============================================\n";
    cout << "Expected avg = 00111110\n";
    start.put('1', 60);
    clk.put('P', 61);
    data.put("00000000", 62);
    avgCalc->evl();
    
    start.put('N', 63);          // negedge start
    data.put("00000000", 64);
    clk.put('1', 65);
    avgCalc->evl();
    
    cout << "\nNegedge of start was received...\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);;

    start.put('0', 66);
    data.put("00000001", 67);    // byte 0
    clk.put('P', 68);            // posedge clk
    avgCalc->evl();

    start.put('0', 69);
    data.put("00000011", 70);    // byte 1
    clk.put('P', 71);            // posedge clk
    avgCalc->evl();

    start.put('0', 72);
    data.put("00000111", 73);    // byte 2
    clk.put('P', 74);            // posedge clk
    avgCalc->evl();

    start.put('0', 75);
    data.put("00001111", 76);    // byte 3
    clk.put('P', 77);            // posedge clk
    avgCalc->evl();

    start.put('0', 78);
    data.put("00011111", 79);    // byte 4
    clk.put('P', 80);            // posedge clk
    avgCalc->evl();

    start.put('0', 81);
    data.put("00111111", 82);    // byte 5
    clk.put('P', 83);            // posedge clk
    avgCalc->evl();

    start.put('0', 84);
    data.put("01111111", 85);    // byte 6
    clk.put('P', 86);            // posedge clk
    avgCalc->evl();

    start.put('0', 87);
    data.put("11111111", 88);    // byte 7
    clk.put('P', 89);            // posedge clk
    avgCalc->evl();

    // display the result
    cout << "\nResults:\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);
    cout << "Test case 3 ends...\n\n";

    // test case 4 (bytes = 10000000, 11000000, 11100000, ..., 11111111)
    // =================================================================
    cout << "Test case 4 begins...\n";
    cout << "=============================================\n";
    cout << "Expected avg = 11100000\n";
    start.put('1', 90);
    clk.put('P', 91);
    data.put("00000000", 92);
    avgCalc->evl();

    start.put('N', 93);          // negedge start
    data.put("00000000", 94);
    clk.put('1', 95);
    avgCalc->evl();

    cout << "\nNegedge of start was received...\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);;

    start.put('0', 96);
    data.put("10000000", 97);    // byte 0
    clk.put('P', 98);            // posedge clk
    avgCalc->evl();

    start.put('0', 99);
    data.put("11000000", 100);    // byte 1
    clk.put('P', 101);            // posedge clk
    avgCalc->evl();

    start.put('0', 102);
    data.put("11100000", 103);    // byte 2
    clk.put('P', 104);            // posedge clk
    avgCalc->evl();

    start.put('0', 105);
    data.put("11110000", 106);    // byte 3
    clk.put('P', 107);            // posedge clk
    avgCalc->evl();

    start.put('0', 108);
    data.put("11111000", 109);    // byte 4
    clk.put('P', 110);            // posedge clk
    avgCalc->evl();

    start.put('0', 111);
    data.put("11111100", 112);    // byte 5
    clk.put('P', 113);            // posedge clk
    avgCalc->evl();

    start.put('0', 114);
    data.put("11111110", 115);    // byte 6
    clk.put('P', 116);            // posedge clk
    avgCalc->evl();

    start.put('0', 117);
    data.put("11111111", 118);    // byte 7
    clk.put('P', 119);            // posedge clk
    avgCalc->evl();

    // display the result
    cout << "\nResults:\n";
    outBit("avg[7:0]", avg);
    outBit("rdy", rdy);
    cout << "Test case 4 ends...\n\n";

    return 0;
}
