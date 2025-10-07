#pragma once

#include <string>
#include <vector>
#include "sqlite3.h"
#include <fstream>
#include <locale>

#include "Structs.h"

namespace MyTestFunctions {
	std::vector<Test> createTest()
	{
		setlocale(LC_ALL, "Ukrainian");

		std::vector<Test> tests;
		Test test;
		Test test1;
		Test test2;
		Test test3;
		Test test4;
		Test test5;
		Test test6;
		Test test7;

		test.setCategory("Mathematics");
		test.setSubCategory("Discrete Mathematics");

		Question q1 = { "How many faces does a cube have?", {"4", "6", "8", "12"}, 2 };
		Question q2 = { "Which number is even?", {"15", "21", "28", "39"}, 3 };
		Question q3 = { "What is the formula for calculating the area of a circle?", {"2Pir", "Pir^2", "Pid", "4Pir^2"}, 2 };
		Question q4 = { "What is the formula for calculating the volume of a cylinder?", {"2Pirh", "Pid^2h", "Pir^2h", "4/3Pir^3"}, 3 };
		Question q5 = { "What is the formula for calculating the area of a triangle?", {"a^2 + b^2 = c^2", "Pir^2", "4/3Pir^3", "1/2 * a * b"}, 4 };
		Question q6 = { "What is the formula for calculating the volume of a sphere?", {"4/3Pir^3", "Pir^2h", "2Pirh", "Pid^2h"}, 1 };
		Question q7 = { "What is the formula for calculating the area of a rectangle?", {"a * b", "2(a + b)", "a^2 + b^2 = c^2", "Pir^2"}, 1 };
		Question q8 = { "What is the formula for calculating the perimeter of a square?", {"2(a + b)", "4a", "a^2 + b^2 = c^2", "Pir^2"}, 2 };
		Question q9 = { "What is the formula for calculating the area of a trapezoid?", {"(a + b)h/2", "a^2 + b^2 = c^2", "Pir^2", "4/3Pir^3"}, 1 };
		Question q10 = { "What is the formula for calculating the volume of a cone?", {"2Pirh", "Pid^2h", "1/3Pir^2h", "4/3Pir^3"}, 3 };

		test.addQuestion(q1);
		test.addQuestion(q2);
		test.addQuestion(q3);
		test.addQuestion(q4);
		test.addQuestion(q5);
		test.addQuestion(q6);
		test.addQuestion(q7);
		test.addQuestion(q8);
		test.addQuestion(q9);
		test.addQuestion(q10);

		test4.setCategory("Математика");
		test4.setSubCategory("Дискретна математика");

		Question q1_31 = { "Скільки граней має куб?", {"4", "6", "8", "12"}, 2 };
		Question q2_31 = { "Яке число є парним?", {"15", "21", "28", "39"}, 3 };
		Question q3_31 = { "Яка формула для обчислення площi кола?", {"2Pir", "Pir^2",  "Pid", "4Pir^2"}, 2 };
		Question q4_31 = { "Яка формула для обчислення об'єму цилiндра?", {"2Pirh", "Pid^2h", "Pir^2h", "4/3Pir^3"}, 3 };
		Question q5_31 = { "Яка формула для обчислення площi трикутника?", {"a^2 + b^2 = c^2", "Pir^2", "4/3Pir^3", "1/2 * a * b"}, 4 };
		Question q6_31 = { "Яка формула для обчислення об'єму кулi?", {"4/3Pir^3", "Pir^2h", "2Pirh", "Pid^2h"}, 1 };
		Question q7_31 = { "Яка формула для обчислення площi прямокутника?", {"a * b", "2(a + b)", "a^2 + b^2 = c^2", "Pir^2"}, 1 };
		Question q8_31 = { "Яка формула для обчислення периметра квадрата?", { "2(a + b)", "4a", "a^2 + b^2 = c^2", "Pir^2"}, 2 };
		Question q9_31 = { "Яка формула для обчислення площi трапецiї?", {"(a + b)h/2", "a^2 + b^2 = c^2", "Pir^2", "4/3Pir^3"}, 1 };
		Question q10_31 = { "Яка формула для обчислення об'єму конуса?", {"2Pirh", "Pid^2h", "1/3Pir^2h", "4/3Pir^3"}, 3 };

		test4.addQuestion(q1_31);
		test4.addQuestion(q2_31);
		test4.addQuestion(q3_31);
		test4.addQuestion(q4_31);
		test4.addQuestion(q5_31);
		test4.addQuestion(q6_31);
		test4.addQuestion(q7_31);
		test4.addQuestion(q8_31);
		test4.addQuestion(q9_31);
		test4.addQuestion(q10_31);

		test1.setCategory("Mathematics");
		test1.setSubCategory("Mathematical Analysis");

		Question q1_1 = { "What is the formula for calculating a derivative?", {
			"f'(x) = f(x) + h",
			"f'(x) = f(x) - h",
			"f'(x) = lim(h→0) (f(x+h) - f(x))/h",
			"f'(x) = f(x) * h"
		}, 3 };

		Question q1_2 = { "What is the formula for calculating an integral?", {
			"∫f(x)dx = f(x) + C",
			"∫f(x)dx = F(x) + C",
			"∫f(x)dx = f'(x) + C",
			"∫f(x)dx = f''(x) + C"
		}, 2 };

		Question q1_3 = { "What is the formula for calculating a limit?", {
			"lim(x→a) f(x) = L",
			"lim(x→a) f(x) = f(a)",
			"lim(x→a) f(x) = f'(a)",
			"lim(x→a) f(x) = f''(a)"
		}, 1 };

		Question q1_4 = { "What is the formula for calculating a geometric series?", {
			"S = a₁ * (1 - r)",
			"S = a₁ + r",
			"S = a₁ - r",
			"S = a₁ / (1 - r)"
		}, 4 };

		Question q1_5 = { "What is the formula for calculating a higher-order derivative?", {
			"f''(x) = d²f/dx²",
			"f''(x) = df/dx",
			"f''(x) = f(x) + h",
			"f''(x) = f(x) - h"
		}, 1 };

		Question q1_6 = { "What is the formula for calculating a partial derivative?", {
			"∂f/∂x = lim(h→0) (f(x+h,y) - f(x,y))/h",
			"∂f/∂x = f(x,y) + h",
			"∂f/∂x = f(x,y) - h",
			"∂f/∂x = f(x,y) * h"
		}, 1 };

		Question q1_7 = { "What is the formula for calculating a double integral?", {
			"∬f(x,y)dA = f(x,y) + C",
			"∬f(x,y)dA = F(x,y) + C",
			"∬f(x,y)dA = f'(x,y) + C",
			"∬f(x,y)dA = f''(x,y) + C"
		}, 2 };

		Question q1_8 = { "What is the formula for calculating a line integral?", {
			"∫C f(x,y)ds = F(x,y) + C",
			"∫C f(x,y)ds = f(x,y) + C",
			"∫C f(x,y)ds = f'(x,y) + C",
			"∫C f(x,y)ds = f''(x,y) + C"
		}, 1 };

		Question q1_9 = { "What is the formula for calculating a Fourier series?", {
			"f(x) ~ a₀/2 + Σ (aₙ cos(nx) + bₙ sin(nx))",
			"f(x) ~ a₀ + Σ (aₙ cos(nx) + bₙ sin(nx))",
			"f(x) ~ a₀/2 + Σ (aₙ sin(nx) + bₙ cos(nx))",
			"f(x) ~ a₀ + Σ (aₙ sin(nx) + bₙ cos(nx))"
		}, 1 };

		Question q1_10 = { "What is the formula for calculating the limit of a function at a point?", {
			"lim(x→a) f(x) = f(a)",
			"lim(x→a) f(x) = f'(a)",
			"lim(x→a) f(x) = L",
			"lim(x→a) f(x) = f''(a)"
		}, 3 };

		test1.addQuestion(q1_1);
		test1.addQuestion(q1_2);
		test1.addQuestion(q1_3);
		test1.addQuestion(q1_4);
		test1.addQuestion(q1_5);
		test1.addQuestion(q1_6);
		test1.addQuestion(q1_7);
		test1.addQuestion(q1_8);
		test1.addQuestion(q1_9);
		test1.addQuestion(q1_10);

		test5.setCategory("Математика");
		test5.setSubCategory("Математичний аналіз");

		Question q1_44 = { "Яка формула для обчислення похідної?", {"f'(x) = f(x) + h", "f'(x) = f(x) - h", "f'(x) = lim(h->0) (f(x+h) - f(x))/h",  "f'(x) = f(x) * h"}, 3 };
		Question q2_44 = { "Яка формула для обчислення інтегралу?", {"∫f(x)dx = f(x) + C", "∫f(x)dx = F(x) + C", "∫f(x)dx = f'(x) + C", "∫f(x)dx = f''(x) + C"}, 2 };
		Question q3_44 = { "Яка формула для обчислення границі?", {"lim(x->a) f(x) = L", "lim(x->a) f(x) = f(a)", "lim(x->a) f(x) = f'(a)", "lim(x->a) f(x) = f''(a)"}, 1 };
		Question q4_44 = { "Яка формула для обчислення ряду?", {"S = a1 * (1 - r)", "S = a1 + r", "S = a1 - r", "S = a1 / (1 - r)"}, 4 };
		Question q5_44 = { "Яка формула для обчислення похідної вищого порядку?", {"f''(x) = d^2f/dx^2", "f''(x) = df/dx", "f''(x) = f(x) + h", "f''(x) = f(x) - h"}, 1 };
		Question q6_44 = { "Яка формула для обчислення часткової похідної?", {"∂f/∂x = lim(h->0) (f(x+h,y) - f(x,y))/h", "∂f/∂x = f(x,y) + h", "∂f/∂x = f(x,y) - h", "∂f/∂x = f(x,y) * h"}, 1 };
		Question q7_44 = { "Яка формула для обчислення подвійного інтегралу?", {"∬f(x,y)dA = f(x,y) + C", "∬f(x,y)dA = F(x,y) + C", "∬f(x,y)dA = f'(x,y) + C", "∬f(x,y)dA = f''(x,y) + C"}, 2 };
		Question q8_44 = { "Яка формула для обчислення криволінійного інтегралу?", {"∫C f(x,y)ds = F(x,y) + C", "∫C f(x,y)ds = f(x,y) + C", "∫C f(x,y)ds = f'(x,y) + C", "∫C f(x,y)ds = f''(x,y) + C"}, 1 };
		Question q9_44 = { "Яка формула для обчислення ряду Фур'є?", {"f(x) ~ a0/2 + Σ (an cos(nx) + bn sin(nx))", "f(x) ~ a0 + Σ (an cos(nx) + bn sin(nx))", "f(x) ~ a0/2 + Σ (an sin(nx) + bn cos(nx))", "f(x) ~ a0 + Σ (an sin(nx) + bn cos(nx))"}, 1 };
		Question q10_44 = { "Яка формула для обчислення границі функції в точці?", {"lim(x->a) f(x) = f(a)", "lim(x->a) f(x) = f'(a)", "lim(x->a) f(x) = L",  "lim(x->a) f(x) = f''(a)"}, 3 };

		test5.addQuestion(q1_44);
		test5.addQuestion(q2_44);
		test5.addQuestion(q3_44);
		test5.addQuestion(q4_44);
		test5.addQuestion(q5_44);
		test5.addQuestion(q6_44);
		test5.addQuestion(q7_44);
		test5.addQuestion(q8_44);
		test5.addQuestion(q9_44);
		test5.addQuestion(q10_44);


		test2.setCategory("Physics");
		test2.setSubCategory("Mechanics");

		Question q2_1 = { "What is the formula for calculating velocity?", {
			"v = s/t",
			"v = at",
			"v = a + b",
			"v = s + t"
		}, 1 };

		Question q2_2 = { "What is the formula for calculating acceleration?", {
			"a = s/v",
			"a = t/v",
			"a = v + t",
			"a = v/t"
		}, 4 };

		Question q2_3 = { "What is the formula for calculating force?", {
			"F = mv",
			"F = ma",
			"F = at",
			"F = s/t"
		}, 2 };

		Question q2_4 = { "What is the formula for calculating work?", {
			"A = F / s",
			"A = F + s",
			"A = F * s",
			"A = F - s"
		}, 3 };

		Question q2_5 = { "What is the formula for calculating energy?", {
			"E = F * s",
			"E = m * g",
			"E = m * a",
			"E = F / t"
		}, 1 };

		Question q2_6 = { "What is the formula for calculating pressure?", {
			"P = F * S",
			"P = F / S",
			"P = S / F",
			"P = F + S"
		}, 2 };

		Question q2_7 = { "What is the formula for calculating volume?", {
			"V = S * h",
			"V = S / h",
			"V = S + h",
			"V = S - h"
		}, 1 };

		Question q2_8 = { "What is the formula for calculating density?", {
			"d = V / m",
			"d = m + V",
			"d = m / V",
			"d = m - V"
		}, 3 };

		Question q2_9 = { "What is the formula for calculating moment of force?", {
			"M = F * r",
			"M = F / r",
			"M = F + r",
			"M = F - r"
		}, 1 };

		Question q2_10 = { "What is the formula for calculating angular velocity?", {
			"w = v * r",
			"w = v + r",
			"w = v - r",
			"w = v / r"
		}, 4 };

		test2.addQuestion(q2_1);
		test2.addQuestion(q2_2);
		test2.addQuestion(q2_3);
		test2.addQuestion(q2_4);
		test2.addQuestion(q2_5);
		test2.addQuestion(q2_6);
		test2.addQuestion(q2_7);
		test2.addQuestion(q2_8);
		test2.addQuestion(q2_9);
		test2.addQuestion(q2_10);

		test6.setCategory("Фiзика");
		test6.setSubCategory("Механiка");

		Question q1_51 = { "Яка формула для обчислення швидкостi?", {"v = s/t", "v = at", "v = a + b", "v = s + t"}, 1 };
		Question q2_51 = { "Яка формула для обчислення прискорення?", {"a = s/v", "a = t/v", "a = v + t", "a = v/t",}, 4 };
		Question q3_51 = { "Яка формула для обчислення сили?", {"F = mv", "F = ma", "F = at", "F = s/t"}, 2 };
		Question q4_51 = { "Яка формула для обчислення роботи?", {"A = F / s", "A = F + s", "A = F * s", "A = F - s"}, 3 };
		Question q5_51 = { "Яка формула для обчислення енергiї?", {"E = F * s", "E = m * g", "E = m * a", "E = F / t"}, 1 };
		Question q6_51 = { "Яка формула для обчислення тиску?", {"P = F * S", "P = F / S", "P = S / F", "P = F + S"}, 2 };
		Question q7_51 = { "Яка формула для обчислення об'єму?", {"V = S * h", "V = S / h", "V = S + h", "V = S - h"}, 1 };
		Question q8_51 = { "Яка формула для обчислення густини?", {"d = V / m", "d = m + V", "d = m / V", "d = m - V"}, 3 };
		Question q9_51 = { "Яка формула для обчислення моменту сили?", {"M = F * r", "M = F / r", "M = F + r", "M = F - r"}, 1 };
		Question q10_51 = { "Яка формула для обчислення кутової швидкостi?", {"w = v * r", "w = v + r", "w = v - r", "w = v / r", }, 4 };

		test6.addQuestion(q1_51);
		test6.addQuestion(q2_51);
		test6.addQuestion(q3_51);
		test6.addQuestion(q4_51);
		test6.addQuestion(q5_51);
		test6.addQuestion(q6_51);
		test6.addQuestion(q7_51);
		test6.addQuestion(q8_51);
		test6.addQuestion(q9_51);
		test6.addQuestion(q10_51);		

		test3.setCategory("Physics");
		test3.setSubCategory("Quantum Physics");

		Question q3_1 = { "What is quantum superposition?", {
			"A state in which a particle is in one definite state",
			"A state in which a particle is in two or more states simultaneously",
			"A state in which a particle has no definite state",
			"A state in which a particle moves at superluminal speed"
		}, 2 };

		Question q3_2 = { "What is quantum entanglement?", {
			"A phenomenon where two particles have independent states",
			"A phenomenon where two particles interact only at short distances",
			"A phenomenon where the state of one particle depends on the state of another, regardless of the distance between them",
			"A phenomenon where a particle moves at superluminal speed"
		}, 3 };

		Question q3_3 = { "What is Heisenberg's uncertainty principle?", {
			"A principle stating that it is impossible to simultaneously measure both the position and momentum of a particle precisely",
			"A principle stating that a particle can be in two places at once",
			"A principle stating that a particle's energy is always positive",
			"A principle stating that a particle has no definite state"
		}, 1 };

		Question q3_4 = { "What is a wave function?", {
			"A function that describes the probability of finding a particle in a certain state",
			"A function that describes the motion of a particle in space",
			"A function that describes the energy of a particle",
			"A function that describes the momentum of a particle"
		}, 1 };

		Question q3_5 = { "What is quantum tunneling?", {
			"A phenomenon where a particle can pass through a potential barrier even if its energy is less than the barrier height",
			"A phenomenon where a particle moves at superluminal speed",
			"A phenomenon where a particle has no definite state",
			"A phenomenon where two particles interact only at short distances"
		}, 1 };

		Question q3_6 = { "What is quantum interference?", {
			"A phenomenon where particle waves overlap, creating zones of reinforcement and cancellation",
			"A phenomenon where a particle moves at superluminal speed",
			"A phenomenon where a particle has no definite state",
			"A phenomenon where two particles interact only at short distances"
		}, 1 };

		Question q3_7 = { "What is quantum decoherence?", {
			"A process in which a quantum system loses its quantum nature and begins to behave like a classical system",
			"A process in which a particle moves at superluminal speed",
			"A process in which a particle has no definite state",
			"A process in which two particles interact only at short distances"
		}, 1 };

		Question q3_8 = { "What is quantum electrodynamics (QED)?", {
			"A theory that describes the interaction of electromagnetic fields with charged particles",
			"A theory that describes the motion of particles in space",
			"A theory that describes the energy of particles",
			"A theory that describes the momentum of particles"
		}, 1 };

		Question q3_9 = { "What is quantum chromodynamics (QCD)?", {
			"A theory that describes the interaction of quarks and gluons",
			"A theory that describes the motion of particles in space",
			"A theory that describes the energy of particles",
			"A theory that describes the momentum of particles"
		}, 1 };

		Question q3_10 = { "What is quantum gravity?", {
			"A theory that attempts to unify quantum mechanics and general relativity",
			"A theory that describes the motion of particles in space",
			"A theory that describes the energy of particles",
			"A theory that describes the momentum of particles"
		}, 1 };

		test3.addQuestion(q3_1);
		test3.addQuestion(q3_2);
		test3.addQuestion(q3_3);
		test3.addQuestion(q3_4);
		test3.addQuestion(q3_5);
		test3.addQuestion(q3_6);
		test3.addQuestion(q3_7);
		test3.addQuestion(q3_8);
		test3.addQuestion(q3_9);
		test3.addQuestion(q3_10);

		test7.setCategory("Фiзика");
		test7.setSubCategory("Квантова фізика");

		Question q1_33 = { "Що таке квантова суперпозиція?", {"Стан, коли частинка знаходиться в одному визначеному стані", "Стан, коли частинка знаходиться в двох або більше станах одночасно", "Стан, коли частинка не має визначеного стану", "Стан, коли частинка рухається з надсвітловою швидкістю"}, 2 };
		Question q2_33 = { "Що таке квантове заплутування?", {"Явище, коли дві частинки мають незалежні стани", "Явище, коли дві частинки взаємодіють лише на короткі відстані", "Явище, коли стан однієї частинки залежить від стану іншої, незалежно від відстані між ними", "Явище, коли частинка рухається з надсвітловою швидкістю"}, 3 };
		Question q3_33 = { "Що таке принцип невизначеності Гейзенберга?", {"Принцип, що стверджує, що неможливо одночасно точно виміряти положення і імпульс частинки", "Принцип, що стверджує, що частинка може бути в двох місцях одночасно", "Принцип, що стверджує, що енергія частинки завжди позитивна", "Принцип, що стверджує, що частинка не має визначеного стану"}, 1 };
		Question q4_33 = { "Що таке хвильова функція?", {"Функція, що описує ймовірність знаходження частинки в певному стані", "Функція, що описує рух частинки в просторі", "Функція, що описує енергію частинки", "Функція, що описує імпульс частинки"}, 1 };
		Question q5_33 = { "Що таке квантова тунельна ефект?", {"Явище, коли частинка може проходити через потенціальний бар'єр, навіть якщо її енергія менша за висоту бар'єра", "Явище, коли частинка рухається з надсвітловою швидкістю", "Явище, коли частинка не має визначеного стану", "Явище, коли дві частинки взаємодіють лише на короткі відстані"}, 1 };
		Question q6_33 = { "Що таке квантова інтерференція?", {"Явище, коли хвилі частинок накладаються одна на одну, утворюючи зони посилення і послаблення", "Явище, коли частинка рухається з надсвітловою швидкістю", "Явище, коли частинка не має визначеного стану", "Явище, коли дві частинки взаємодіють лише на короткі відстані"}, 1 };
		Question q7_33 = { "Що таке квантова декогеренція?", {"Процес, при якому квантова система втрачає свою квантову природу і починає вести себе як класична система", "Процес, при якому частинка рухається з надсвітловою швидкістю", "Процес, при якому частинка не має визначеного стану", "Процес, при якому дві частинки взаємодіють лише на короткі відстані"}, 1 };
		Question q8_33 = { "Що таке квантова електродинаміка (КЕД)?", {"Теорія, що описує взаємодію електромагнітного поля з зарядженими частинками", "Теорія, що описує рух частинок в просторі", "Теорія, що описує енергію частинок", "Теорія, що описує імпульс частинок"}, 1 };
		Question q9_33 = { "Що таке квантова хромодинаміка (КХД)?", {"Теорія, що описує взаємодію кварків і глюонів", "Теорія, що описує рух частинок в просторі", "Теорія, що описує енергію частинок", "Теорія, що описує імпульс частинок"}, 1 };
		Question q10_33 = { "Що таке квантова гравітація?", {"Теорія, що намагається об'єднати квантову механіку і загальну теорію відносності", "Теорія, що описує рух частинок в просторі", "Теорія, що описує енергію частинок", "Теорія, що описує імпульс частинок"}, 1 };

		test7.addQuestion(q1_33);
		test7.addQuestion(q2_33);
		test7.addQuestion(q3_33);
		test7.addQuestion(q4_33);
		test7.addQuestion(q5_33);
		test7.addQuestion(q6_33);
		test7.addQuestion(q7_33);
		test7.addQuestion(q8_33);
		test7.addQuestion(q9_33);
		test7.addQuestion(q10_33);


		tests.push_back(test);
		tests.push_back(test1);
		tests.push_back(test2);
		tests.push_back(test3);
		tests.push_back(test4);
		tests.push_back(test5);
		tests.push_back(test6);
		tests.push_back(test7);

		return tests;
	};
}
