package com.FranckBarbier.Java;

class Pair<F, S> {

    final F first;
    final S second;

    public Pair(F first, S second) {
        this.first = first;
        this.second = second;
    }
}

public class Palindrome {
// Obligatoire car on ne peut pas hériter de 'String' :

    private String _palindrome = "";

// On ne peut pas faire de tableaux primitifs contenant des objets issus de classe générique d'où :
    private static final java.util.Vector<Pair<Character, Character>> _Intervals = new java.util.Vector<>();

    static {
        _Intervals.add(new Pair<>('a', 'z'));
        _Intervals.add(new Pair<>('A', 'Z'));
    }

    // Cela fonctionne :
//    private static final Pair<Character, Character> _Intervalx[];
    // Cela ne fonctionne pas ('generic array creation') :
//    private static final Pair<Character, Character> _Intervals[] = {new Pair<>('a', 'z'), new Pair<>('A', 'Z')};
    // Cela ne fonctionne pas non plus ('generic array creation') :
//     private static final Pair<Character, Character> _Intervals[] = new Pair<Character, Character>[2];
    public Palindrome(String palindrome) {
        for (int i = 0; i < palindrome.length(); ++i) {
            for (int j = 0; j < _Intervals.size(); ++j) {
                if (palindrome.charAt(i) >= _Intervals.get(j).first && palindrome.charAt(i) <= _Intervals.get(j).second) {
                    _palindrome += palindrome.charAt(i);
                    break;
                }
            }
        }

    }

    public boolean isPalindrome() {
        for (int i = 0; i < _palindrome.length() / 2; ++i) {
            if (Character.toLowerCase(_palindrome.charAt(i)) != Character.toLowerCase(_palindrome.charAt(_palindrome.length() - 1 - i))) {
                return false;
            }
        }
        return true;
    }

    public String toString() {
        return _palindrome;
    }

    public static void main(String[] args) {
        Palindrome p1 = new Palindrome("Elu par cette crapule"); // French
        Palindrome p2 = new Palindrome("Esope reste ici et se repose"); // French
        Palindrome p3 = new Palindrome("Was it a car or a cat I saw?"); // English
        Palindrome p4 = new Palindrome("This is not a palindrome"); // English
        System.out.println(p1.toString() + ": " + (p1.isPalindrome() ? "true" : "false") + '\n'); // 'true'
        System.out.println(p2.toString() + ": " + (p2.isPalindrome() ? "true" : "false") + '\n'); // 'true'
        System.out.println(p3.toString() + ": " + (p3.isPalindrome() ? "true" : "false") + '\n'); // 'true'
        System.out.println(p4.toString() + ": " + (p4.isPalindrome() ? "true" : "false") + '\n'); // 'false'
    }
}
