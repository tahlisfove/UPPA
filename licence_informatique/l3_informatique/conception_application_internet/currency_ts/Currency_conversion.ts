enum Currency_ISO_symbols {
    Bitcoin = "XBT",
    Dollar = "USD",
    Euro = "EUR",
    Lats = "LVL",
    Moroccan_Dirham = "MAD"
    // Etc.
}

export default Currency_ISO_symbols;

export class Currency_conversion {
    private static _Data = new Promise((success, failure) => {
        console.log("Calling Web service...");
        const request: XMLHttpRequest = new XMLHttpRequest();
        request.onreadystatechange = () => {
            console.log(request.getAllResponseHeaders());
            if (request.readyState === XMLHttpRequest.DONE) {
                const data_type: null | string = request.getResponseHeader("Content-Type");
                if (data_type !== null && data_type.includes("application/json")) {
                    /** TEST */
                    const response = JSON.parse(request.responseText);
                    console.log("For 1 US Dollar (USD) to MAD (Moroccan Dirham): " + response.rates.MAD);
                    /** End of TEST */
                    success(JSON.parse(request.responseText));
                } else failure("No data...");
            }
        };
        request.open("GET", "http://openexchangerates.org/api/latest.json" + "?app_id=" + "678cd96edd4b4f3eb637bf74ef8e0815", true); // This Web site requires a license key after signing in
// 'request' must already be opened:
        request.send(null);
    });

    public static async Convert(currency_ISO_symbol: Currency_ISO_symbols): Promise<number> {
        const data: any = await Currency_conversion._Data;
        console.log(typeof data.rates[currency_ISO_symbol] + " <-'typeof' " + data.rates[currency_ISO_symbol]);
        return data.rates[currency_ISO_symbol];
    }
}

