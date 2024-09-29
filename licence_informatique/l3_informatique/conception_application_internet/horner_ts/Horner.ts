interface Monomial {
    coefficient: number;
    power: number;
}

const polynomial = new Array<Monomial>();
polynomial.push({coefficient: 3, power: 4}, {coefficient: -2, power: 1}, {coefficient: 5, power: 0});

function horner_method(x: number, polynomial: Array<Monomial>) {
    console.assert(polynomial.length !== 0, "'polynomial.length === 0', why?");
    let result = 0;
    let prior_monomial_index: null | number = null;
    for (let i = 0; i < polynomial.length; i++) {
        if (prior_monomial_index !== null) {
            console.assert(polynomial[i].power < polynomial[prior_monomial_index].power, "'polynomial[i].power >= polynomial[prior_monomial_index].power', why?");
            result += polynomial[prior_monomial_index].coefficient;
            for (let j = polynomial[prior_monomial_index].power; j > polynomial[i].power; j--)
                result *= x;
        }
        prior_monomial_index = i;
    }

    if (prior_monomial_index !== null) {
        result += polynomial[prior_monomial_index].coefficient;
        for (let j = polynomial[prior_monomial_index].power; j > 0; j--)
            result *= x;
    }

    return result;
}

const x = 2;
console.log("horner_method(" + x + ", " + JSON.stringify(polynomial) + "): " + horner_method(x, polynomial));
