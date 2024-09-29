enum Result {
    Format = "Format invalid",
    Key = "Key invalid",
    Ok = "Ok",
}

export default class N_INSEE {
    private static readonly _Format: RegExp = new RegExp("^(?!000)(\\d{13}$)");
    private _result: Result;
    get result(): Result {
        return this._result;
    }

    constructor(private readonly _n_insee: number, private readonly _clef: number) { // 'public' by default
        // 'this._n_insee' is automatically inserted as private field
        // 'this._clef' is automatically inserted as private field
        if (this._n_insee.toString().match(N_INSEE._Format)) {
            if (this._calcul_clef())
                this._result = Result.Ok;
            else this._result = Result.Key;
        } else
            this._result = Result.Format;
    }

    private _calcul_clef(): boolean {
        if ((97 - (this._n_insee % 97)) === this._clef)
            return true;
        else
            return false;
    }
}
