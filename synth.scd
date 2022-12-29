(
s.boot;
thisProcess.openUDPPort(1337);
//OSCFunc.trace(true);

~synth = {
	arg pitch = 666, volume = 0.5;
	SinOsc.ar(pitch, 0, volume)!2
}.play;

OSCFunc(~func, '/theremin');

~func = {
		arg msg;
		~pitch = msg[1] / 10;
		~volume = 10000 / msg[2];

		~pitch.postln;
		~volume.postln;

		~synth.set(\pitch, ~pitch);
		~synth.set(\volume, ~volume);
	}
)


















// Pbind(\degree, Pseries(0, 1, 30), \dur, 0.05).play;
// Pbind(\degree, Pseq([0, 1, 2, 3, 4, 5, 6, 7], 1), \dur, 0.2).play;
// Pbind(\degree, Pseq([0, 1, 2, 3, 4, 5, 6, 7], 5), \dur, Pseq([0.2, 0.1, 0.1, 0.2,
// 0.2, 0.35], inf)).play;