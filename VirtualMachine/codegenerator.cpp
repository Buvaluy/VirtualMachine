#include "codegenerator.h"

CodeGenerator::CodeGenerator()
{
  mCode.insert("nop", "00");
  mCode.insert("in",  "01");
  mCode.insert("out", "02");
  mCode.insert("iret", "03");
  mCode.insert("wrrb", "04");
  mCode.insert("wrsp", "05");
  mCode.insert("push", "06"); // работает с регистрами. регистр меняют POH.
  mCode.insert("pop", "07");  // SP указатель на верхушку стека
  mCode.insert("ret", "08");
  mCode.insert("htl", "09");
  mCode.insert("jmp", "10");
  mCode.insert("jz", "11");
  mCode.insert("jnz", "12");
  mCode.insert("js", "13");
  mCode.insert("jns", "14");
  mCode.insert("jo", "15");
  mCode.insert("jno", "16");
  mCode.insert("jrnz", "17");
  mCode.insert("int", "18");
  mCode.insert("call", "19");
  mCode.insert("rd", "21");
  mCode.insert("wr", "22");
  mCode.insert("add", "23");
  mCode.insert("sub", "24");
  mCode.insert("mul", "25");
  mCode.insert("div", "26");
  mCode.insert("ei", "28");
  mCode.insert("di", "29");
  mCode.insert("movR", "30");//регистр
  mCode.insert("rdR", "31");//регистр
  mCode.insert("wrR", "32");//регистр
  mCode.insert("addR", "33");//регистр
  mCode.insert("subR", "34");//регистр
  mCode.insert("mulR", "35");//регистр
  mCode.insert("divR", "36");//регистр
  mCode.insert("in", "37");
  mCode.insert("out", "38");
  mCode.insert("rdi", "41");
  mCode.insert("adi", "43");
  mCode.insert("sbi", "44");
  mCode.insert("muli", "45");
  mCode.insert("divi", "46");
}

QString CodeGenerator::getCode(QString code)
{
  return mCode.value(code, "-1");
}
