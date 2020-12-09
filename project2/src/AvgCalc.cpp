#include "AvgCalc.h"

AvgCalc::AvgCalc(Wire& start_, Wire& clk_, WireV& data_, WireV& avg_, Wire& rdy_) :
    start(&start_), clk(&clk_), data(&data_), avg(&avg_), rdy(&rdy_)
{    
	// initialize internal variables
    counter         = 0;
    avg_content     = "";
    avg_event_time  = 0;

    // initialize internal wires and variables
    a0L = new Wire('0', 0); a1L = new Wire('0', 0); a2L = new Wire('0', 0); a3L = new Wire('0', 0);
    a4L = new Wire('0', 0); a5L = new Wire('0', 0); a6L = new Wire('0', 0); a7L = new Wire('0', 0);
    a8L = new Wire('0', 0); a9L = new Wire('0', 0); aAL = new Wire('0', 0);

    sum0L = new Wire('0', 0); sum1L = new Wire('0', 0); sum2L = new Wire('0', 0); sum3L = new Wire('0', 0);
    sum4L = new Wire('0', 0); sum5L = new Wire('0', 0); sum6L = new Wire('0', 0); sum7L = new Wire('0', 0);
    sum8L = new Wire('0', 0); sum9L = new Wire('0', 0); sumAL = new Wire('0', 0);

    ci0L = new Wire('0', 0); co0L = new Wire('0', 0); co1L = new Wire('0', 0); co2L = new Wire('0', 0);
    co3L = new Wire('0', 0); co4L = new Wire('0', 0); co5L = new Wire('0', 0); co6L = new Wire('0', 0);
    co7L = new Wire('0', 0); co8L = new Wire('0', 0); co9L = new Wire('0', 0); coAL = new Wire('0', 0);
   
    data0L = new Wire('0', 0); data1L = new Wire('0', 0);
    data2L = new Wire('0', 0); data3L = new Wire('0', 0);
    data4L = new Wire('0', 0); data5L = new Wire('0', 0);
    data6L = new Wire('0', 0); data7L = new Wire('0', 0);

    b8L = new Wire('0', 0); b9L = new Wire('0', 0); bAL = new Wire('0', 0);

    // instantiate full-adders (combinational logic)
    fa0 = new FullAdder(*a0L, *data0L, *ci0L, *co0L, *sum0L);
    fa1 = new FullAdder(*a1L, *data1L, *co0L, *co1L, *sum1L);
    fa2 = new FullAdder(*a2L, *data2L, *co1L, *co2L, *sum2L);
    fa3 = new FullAdder(*a3L, *data3L, *co2L, *co3L, *sum3L);
    fa4 = new FullAdder(*a4L, *data4L, *co3L, *co4L, *sum4L);
    fa5 = new FullAdder(*a5L, *data5L, *co4L, *co5L, *sum5L);
    fa6 = new FullAdder(*a6L, *data6L, *co5L, *co6L, *sum6L);
    fa7 = new FullAdder(*a7L, *data7L, *co6L, *co7L, *sum7L);
    fa8 = new FullAdder(*a8L, *b8L, *co7L, *co8L, *sum8L);
    fa9 = new FullAdder(*a9L, *b9L, *co8L, *co9L, *sum9L);
    faA = new FullAdder(*aAL, *bAL, *co9L, *coAL, *sumAL);

    // instantiate D flip-flops with set/reset
    dff0 = new DffSR(*sum0L, *clk, *start, *a0L, 0, 0);
    dff1 = new DffSR(*sum1L, *clk, *start, *a1L, 0, 0);
    dff2 = new DffSR(*sum2L, *clk, *start, *a2L, 0, 0);
    dff3 = new DffSR(*sum3L, *clk, *start, *a3L, 0, 0);
    dff4 = new DffSR(*sum4L, *clk, *start, *a4L, 0, 0);
    dff5 = new DffSR(*sum5L, *clk, *start, *a5L, 0, 0);
    dff6 = new DffSR(*sum6L, *clk, *start, *a6L, 0, 0);
    dff7 = new DffSR(*sum7L, *clk, *start, *a7L, 0, 0);
    dff8 = new DffSR(*sum8L, *clk, *start, *a8L, 0, 0);
    dff9 = new DffSR(*sum9L, *clk, *start, *a9L, 0, 0);
    dffA = new DffSR(*sumAL, *clk, *start, *aAL, 0, 0);

    // init D flip-flops
    dff0->init(float(0.37), '1'); dff1->init(float(0.37), '1'); dff2->init(float(0.37), '1');
    dff3->init(float(0.37), '1'); dff4->init(float(0.37), '1'); dff5->init(float(0.37), '1');
    dff6->init(float(0.37), '1'); dff7->init(float(0.37), '1'); dff8->init(float(0.37), '1');
    dff9->init(float(0.37), '1'); dffA->init(float(0.37), '1');

    // call the probability functions
    fa0->prob(); fa1->prob(); fa2->prob(); fa3->prob(); fa4->prob(); fa5->prob();
    fa6->prob(); fa7->prob(); fa8->prob(); fa9->prob(); faA->prob();
    dff0->prob(); dff1->prob(); dff2->prob(); dff3->prob(); dff4->prob(); dff5->prob();
    dff6->prob(); dff7->prob(); dff8->prob(); dff9->prob(); dffA->prob();
}

void AvgCalc::evl() {

    // update the counter
    if (start->value == 'N') {
        counter = 0;
    } else if (clk->value == 'P') {
        if (counter != 8) {
            counter++;
        } 
    }

    #ifdef DEBUG
        cout << "counter: " << counter << "\n";
    #endif // DEBUG

    // read the content of 'data'
    data->get(data_content, data_event_time);

    data0L->put(data_content[7], data_event_time); data1L->put(data_content[6], data_event_time);
    data2L->put(data_content[5], data_event_time); data3L->put(data_content[4], data_event_time);
    data4L->put(data_content[3], data_event_time); data5L->put(data_content[2], data_event_time);
    data6L->put(data_content[1], data_event_time); data7L->put(data_content[0], data_event_time);

    #ifdef DEBUG
        cout << "data_content: " << data_content << "\n";
        cout <<  data7L->value << ", " << data6L->value << ", " << data5L->value << ", " <<
                 data4L->value << ", " << data3L->value << ", " << data3L->value << ", " <<
                 data1L->value << ", " << data0L->value << "\n\n";
    #endif // DEBUG
    
    // process the content of data - datacall evl() functions of components in order
    fa0->evl(); fa1->evl(); fa2->evl(); fa3->evl(); fa4->evl(); fa5->evl();
    fa6->evl(); fa7->evl(); fa8->evl(); fa9->evl(); faA->evl();
    
    #ifdef DEBUG
        cout << "sum 0, co0: " << sum0L->value << ", " << co0L->value << "\n";
        cout << "sum 1, co1: " << sum1L->value << ", " << co1L->value << "\n";
        cout << "sum 2, co2: " << sum2L->value << ", " << co2L->value << "\n";
        cout << "sum 3, co3: " << sum3L->value << ", " << co3L->value << "\n";
        cout << "sum 4, co4: " << sum4L->value << ", " << co4L->value << "\n";
        cout << "sum 5, co5: " << sum5L->value << ", " << co5L->value << "\n";
        cout << "sum 6, co6: " << sum6L->value << ", " << co6L->value << "\n";
        cout << "sum 7, co7: " << sum7L->value << ", " << co7L->value << "\n";
        cout << "sum 8, co8: " << sum8L->value << ", " << co8L->value << "\n";
        cout << "sum 9, co9: " << sum9L->value << ", " << co9L->value << "\n";
        cout << "sum A, coA: " << sumAL->value << ", " << coAL->value << "\n\n";
    #endif // DEBUG

    dff0->evl(); dff1->evl(); dff2->evl(); dff3->evl(); dff4->evl(); dff5->evl();
    dff6->evl(); dff7->evl(); dff8->evl(); dff9->evl(); dffA->evl();

    #ifdef DEBUG
        cout << "a0L: " << a0L->value << "\n";
        cout << "a1L: " << a1L->value << "\n";
        cout << "a2L: " << a2L->value << "\n";
        cout << "a3L: " << a3L->value << "\n";
        cout << "a4L: " << a4L->value << "\n";
        cout << "a5L: " << a5L->value << "\n";
        cout << "a6L: " << a6L->value << "\n";
        cout << "a7L: " << a7L->value << "\n";
        cout << "a8L: " << a8L->value << "\n";
        cout << "a9L: " << a9L->value << "\n";
        cout << "aAL: " << aAL->value << "\n\n";
    #endif // DEBUG

    // update 'avg' and 'rdy'
    if (counter == 8) {
        if (rdy->value != '1') {
            // the results of computation
            avg_content.push_back(aAL->value);
            avg_content.push_back(a9L->value);
            avg_content.push_back(a8L->value);
            avg_content.push_back(a7L->value);
            avg_content.push_back(a6L->value);
            avg_content.push_back(a5L->value);
            avg_content.push_back(a4L->value);
            avg_content.push_back(a3L->value);
            avg_event_time = aAL->eventTime;

            avg->put(avg_content, avg_event_time);
            rdy->put('1', avg_event_time);
        }
        #ifdef DEBUG
        cout << "counter = " << counter << "\n";
                cout << "avg_content = " << avg_content << "\n";
                cout << "avg_event_time = " << avg_event_time << "\n";
        #endif // DEBUG
    } else {
        avg_content = "";
        avg->put(avg_content, avg_event_time);
        rdy->put('0', avg_event_time);
    }
}
