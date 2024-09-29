

async function googleTranslation(expression, langSrc, langDst, actionFunc) {

  let data = {
    expression: expression,
    languageSrc: langSrc,
    languageDst: langDst,
    translatedExpr: '',
    error: false,
  };

  try {
    let url = "https://translate.googleapis.com/translate_a/single?client=gtx";
    url += `&sl=${langSrc}&tl=${langDst}&dt=t&q=${escape(expression)}`;
    let params = { method: 'GET' };

    const json = await fetch(url, params).then(response => response.json());

    data.translatedExpr = json[0][0][0];
  } catch (error) {
    console.log('Erreur fetch : '+error.message);
    data.error = true;
  }

  actionFunc(data);
}
