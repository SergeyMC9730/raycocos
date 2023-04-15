#pragma once

namespace Easings {
	float update_inSine(float x);
	float update_outSine(float x);
	float update_inOutSine(float x);

	float update_linear(float x);

	float update_inQuad(float x);
	float update_outQuad(float x);
	float update_inOutQuad(float x);

	float update_inCubic(float x);
	float update_outCubic(float x);
	float update_inOutCubic(float x);

	float update_inQuart(float x);
	float update_outQuart(float x);
	float update_inOutQuart(float x);

	float update_inQuint(float x);
	float update_outQuint(float x);
	float update_inOutQuint(float x);

	float update_inExpo(float x);
	float update_outExpo(float x);
	float update_inOutExpo(float x);

	float update_inCirc(float x);
	float update_outCirc(float x);
	float update_inOutCirc(float x);

	float update_inBack(float x);
	float update_outBack(float x);
	float update_inOutBack(float x);

	float update_inElastic(float x);
	float update_outElastic(float x);
	float update_inOutElastic(float x);

	float update_inBounce(float x);
	float update_outBounce(float x);
	float update_inOutBounce(float x);
}

enum Easing {
	E_LINEAR = 0,
	E_INSINE,
	E_OUTSINE,
	E_INOUTSINE,
	E_INQUAD,
	E_OUTQUAD,
	E_INOUTQUAD,
	E_INCUBIC,
	E_OUTCUBIC,
	E_INOUTCUBIC,
	E_INQUART,
	E_OUTQUART,
	E_INOUTQUART,
	E_INQUINT,
	E_OUTQUINT,
	E_INOUTQUINT,
	E_INEXPO,
	E_OUTEXPO,
	E_INOUTEXPO,
	E_INCIRC,
	E_OUTCIRC,
	E_INOUTCIRC,
	E_INBACK,
	E_OUTBACK,
	E_INOUTBACK,
	E_INELASTIC,
	E_OUTELASTIC,
	E_INOUTELASTIC,
	E_INBOUNCE,
	E_OUTBOUNCE,
	E_INOUTBOUNCE
};