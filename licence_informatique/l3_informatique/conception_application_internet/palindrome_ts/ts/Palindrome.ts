enum Comparable_ {LessThan, Equal, GreaterThan}

interface Comparable<T> { // Similar to Java "functional interface"
    compareTo(t: T): Comparable_;
}

interface Pair<T> extends Comparable<Pair<T>> {
    readonly _first: T; // Cannot be 'private'...
    readonly _second: T;
    description?: string;
}

abstract class Complex implements Pair<number> {
    constructor(readonly _first: number, readonly _second: number) {
    }

    abstract compareTo(t: Pair<number>): Comparable_;

    // description: string; // 'description' is optional in 'Pair<T>'
}

class Palindrome_authorized_interval implements Pair<string> {
    // Caution: attributes from interface *MUST* be repeated here...
    // This is done through constructor:
    constructor(readonly _first: string, readonly _second: string) {
    }

    compareTo(t: Pair<string>): Comparable_ { // 'public' by default
        if (this._first.localeCompare(t._first) === -1 &&
            this._second.localeCompare(t._second) === -1) return Comparable_.LessThan;
        if (this._first.localeCompare(t._first) === 0 &&
            this._second.localeCompare(t._second) === 0) return Comparable_.Equal;
        if (this._first.localeCompare(t._first) === 1 &&
            this._second.localeCompare(t._second) === 1) return Comparable_.GreaterThan;
    }

    // 'private' -> error because 'public' in 'Pair<T>':
    description: string; // May be omitted because optional in 'Pair<T>'

    set_description(/* 'readonly' -> constructor only! */ description: string): void { // 'public' by default
        this.description = description;
    }
}

class Palindrome {

    private static readonly _Intervals: ReadonlyArray<Palindrome_authorized_interval> = [new Palindrome_authorized_interval('a', 'z'), new Palindrome_authorized_interval('A', 'Z')];

    private _palindrome: string = "";

    constructor(private readonly string: string) { // 'public' by default
        // 'this._palindrome' is automatically inserted as private field
        for (let character of string) { // A 'string' object is an example of a built-in iterable object
            // See also: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Iteration_protocols#The_iterable_protocol
            Palindrome._Intervals.forEach(element => {
                if (character >= element._first && character <= element._second) {
                    this._palindrome += character;
                    return; // From 'forEach' <=> 'break' when using native 'for'
                }
            });
        }
    }

    isPalindrome(): boolean { // 'public' by default
        for (let i: number = 0; i < this._palindrome.length / 2; ++i) {
            if (this._palindrome.charAt(i).toLowerCase() !== this._palindrome.charAt(this._palindrome.length - 1 - i).toLowerCase()) {
                return false;
            }
        }
        return true;
    }

    toString(): string { // 'public' by default
        return this._palindrome;
    }
}

const main = () => { // 'window.onload = main;'
    let p = new Palindrome("Elu par cette crapule");
    window.confirm(p.toString() + ": " + p.isPalindrome()); // 'true'
}



