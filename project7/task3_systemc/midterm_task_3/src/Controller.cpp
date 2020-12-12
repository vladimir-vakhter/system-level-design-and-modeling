#include "Controller.h"

void Controller::evl_comp_outputs()
{
	// set outputs to inactive values
	ready	= SC_LOGIC_0;
	in0C	= SC_LOGIC_0;
	incC	= SC_LOGIC_0;
	ldx		= SC_LOGIC_0;
	ldT		= SC_LOGIC_0;
	in1T	= SC_LOGIC_0;
	ldR		= SC_LOGIC_0;
	in1R	= SC_LOGIC_0;
	
	switch (p_state)
	{
	case IDLE:
		ready	= SC_LOGIC_1;
		in0C	= SC_LOGIC_0;
		incC	= SC_LOGIC_0;
		ldx		= SC_LOGIC_0;
		ldT		= SC_LOGIC_0;
		in1T	= SC_LOGIC_0;
		ldR		= SC_LOGIC_0;
		in1R	= SC_LOGIC_0;
		break;
	case LOAD:
		ready	= SC_LOGIC_0;
		in0C	= SC_LOGIC_1;	// initialize counter by zero
		incC	= SC_LOGIC_0;
		ldx		= SC_LOGIC_1;	// load X
		ldT		= SC_LOGIC_0;
		in1T	= SC_LOGIC_1;	// set term to one
		ldR		= SC_LOGIC_0;
		in1R	= SC_LOGIC_1;	// set result to one
		break;
	case TERM:
		ready	= SC_LOGIC_0;
		in0C	= SC_LOGIC_0;
		incC	= SC_LOGIC_0;
		ldx		= SC_LOGIC_0;
		ldT		= SC_LOGIC_1;	// load term
		in1T	= SC_LOGIC_0;
		ldR		= SC_LOGIC_0;
		in1R	= SC_LOGIC_0;
		break;
	case RES:
		ready	= SC_LOGIC_0;
		in0C	= SC_LOGIC_0;
		incC	= SC_LOGIC_1;	// increment counter
		ldx		= SC_LOGIC_0;
		ldT		= SC_LOGIC_0;
		in1T	= SC_LOGIC_0;
		ldR		= SC_LOGIC_1;	// load result
		in1R	= SC_LOGIC_0;
		break;
	default:
		ready	= SC_LOGIC_0;
		in0C	= SC_LOGIC_0;
		incC	= SC_LOGIC_0;
		ldx		= SC_LOGIC_0;
		ldT		= SC_LOGIC_0;
		in1T	= SC_LOGIC_0;
		ldR		= SC_LOGIC_0;
		in1R	= SC_LOGIC_0;
		break;
	}
}

void Controller::evl_comb_states()
{
	// next state/output logic
	switch (p_state.read())
	{
		case IDLE:
			if (go == '1') n_state = LOAD;
			else n_state = IDLE;
			break;
		case LOAD:
			if (go == '0') n_state = TERM;
			else n_state = LOAD;
			break;
		case TERM:
			n_state = RES;
			break;
		case RES:
			if (coC == '0') n_state = TERM;
			else n_state = IDLE;
			break;
		default:
			n_state = IDLE;
			break;
	}
}

void Controller::evl_sequential()
{
	while (true) {
		if (rst == '1') p_state = IDLE;
		else if (clk->event() && (clk == '1')) p_state = n_state;
		wait();
	}
}
