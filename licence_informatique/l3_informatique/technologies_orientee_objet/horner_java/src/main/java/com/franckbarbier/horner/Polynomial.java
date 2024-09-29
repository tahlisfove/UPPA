package com.franckbarbier.horner;

public class Polynomial {

    private java.util.Map<Integer, Double> _polynomial = new java.util.HashMap<>();

    Polynomial() {
        _polynomial.put(1, -12.D);
        _polynomial.put(39, 8.D);
    }

    public double horner_method(final double x) {
        java.util.List<Integer> x_powers = _polynomial.keySet().stream().collect(java.util.stream.Collectors.toList());
        java.util.Collections.sort(x_powers, java.util.Collections.reverseOrder());
//        for (int power : x_powers) {
//            System.out.println("power: " + power);
//        }
        double result = 0.D;
        int prior_x_power = -1; // For simplication, powers of 'x' are positive integers...
        for (int i = 0; i < x_powers.size(); i++) { // 39, 1
            if (prior_x_power != -1) {
                assert (x_powers.get(i) < x_powers.get(prior_x_power)); // Because of 'sort'...
                result += _polynomial.get(x_powers.get(prior_x_power));
                for (int j = x_powers.get(prior_x_power); j > x_powers.get(i); j--) {
                    result *= x;
                }
            }
            prior_x_power = i;
        }
        if (prior_x_power != -1) {
            result += _polynomial.get(x_powers.get(prior_x_power));
            for (int j = x_powers.get(prior_x_power); j > 0; j--) {
                result *= x;
            }
        }
        return result;
    }

    public void print() {
        _polynomial.forEach((power, coefficient) -> System.out.print(coefficient + "*x" + power + " + "));
        System.out.print("0\n\n");
    }
}
