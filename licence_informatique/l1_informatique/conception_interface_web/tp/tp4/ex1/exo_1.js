console.log("exo_1.js");

function plusGrand2(n1, n2){
  let res;
  if(n1>n2){
    res = n1;
  }
  else{
    res=n2;
  }
  return res;
}

function plusGrand3(n1, n2, n3){
  let res;
  if ((n1>n2)&&(n1>n3)){
    res=n1;
  }
  else{
    if(n2>n3){
      res=n2;
    }
    else{
      res=n3
    }
  }
  return res;
}
