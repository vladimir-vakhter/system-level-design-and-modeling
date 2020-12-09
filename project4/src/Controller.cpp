#include "Controller.h"

void Controller::evl_comp_outputs()
{
	// set outputs to inactive values
	rdy = SC_LOGIC_0;
	ce	= SC_LOGIC_0;
	en	= SC_LOGIC_1;
	zer = SC_LOGIC_1;
	
	switch (p_state)
	{
	case st1_initialize:
		rdy = SC_LOGIC_0;
		ce	= SC_LOGIC_0;
		en	= SC_LOGIC_1;
		zer = SC_LOGIC_1;
		break;
	case st2_wait_on_start:
		rdy = SC_LOGIC_0;
		ce	= SC_LOGIC_0;
		en	= SC_LOGIC_1;
		zer = SC_LOGIC_1;
		break;
	case st3_calculate:
		rdy = SC_LOGIC_0;
		ce	= SC_LOGIC_1;
		en	= SC_LOGIC_1;
		zer = SC_LOGIC_0;
		break;
	case st4_calc_complete:
		rdy = SC_LOGIC_0;
		ce	= SC_LOGIC_0;
		en	= SC_LOGIC_1;
		zer = SC_LOGIC_0;
		break;
	case st5_average_is_valid:
		rdy = SC_LOGIC_1;
		ce	= SC_LOGIC_0;
		en	= SC_LOGIC_0;
		zer = SC_LOGIC_0;
		break;
	default:
		rdy = SC_LOGIC_0;
		ce	= SC_LOGIC_0;
		en	= SC_LOGIC_1;
		zer = SC_LOGIC_1;
		break;
	}
}

void Controller::evl_comb_states()
{
	// next state/output logic
	switch (p_state.read())
	{
		case st1_initialize:
			if (start == '1') n_state = st2_wait_on_start;
			else n_state = st1_initialize;
			break;
		case st2_wait_on_start:
			if (start == '0') n_state = st3_calculate;
			else n_state = st2_wait_on_start;
			break;
		case st3_calculate:
			if (co.read() == sc_lv<3>("111")) n_state = st4_calc_complete;
			else n_state = st3_calculate;
			break;
		case st4_calc_complete:
			n_state = st5_average_is_valid;
			break;
		case st5_average_is_valid:
			if (start == '1') n_state = st2_wait_on_start;
			else n_state = st5_average_is_valid;
			break;
		default:
			n_state = st1_initialize;
			break;
	}
}

void Controller::evl_sequential()
{
	while (true) {
		if (rst == '1') p_state = st1_initialize;
		else if (clk->event() && (clk == '1')) p_state = n_state;
		wait();
	}
}
