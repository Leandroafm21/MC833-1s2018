package com.unicamp.redes.server;

import java.util.ArrayList;

public class Disciplina {
    private String codigo;
    private String ementa;
    private String textoAula;
    private String horario;

    private static ArrayList<Disciplina> _lista = null;

    public static ArrayList<Disciplina> GetList()
    {
        return _lista;
    }

    public static void AddToList(Disciplina disc)
    {
        if (_lista == null)
          _lista = new ArrayList<Disciplina>();
        _lista.add(disc);
    }

    public static String ListSubjects()
    {

        if (_lista == null)
          return "";
        String ret = "";
        for (Disciplina disc : _lista)
        {
            ret += disc.codigo + "\n";
        }
        return ret;
    }

    public static Disciplina GetByCodigo(String codigo) {
        if (_lista == null)
            return null;
        for (Disciplina disc : _lista)
            if (disc.codigo.equalsIgnoreCase(codigo))
                return disc;
        return null;
    }

    public static String GetInfoAll() {
        String ret = "";
        for (Disciplina disc: _lista)
            ret += disc.getInfo();
        return ret;
    }

    public Disciplina(String codigo, String ementa, String horario)
    {
        this.codigo = codigo;
        this.ementa = ementa;
        this.horario = horario;
    }

    public void AtualizaTextoAula(String textoAula)
    {
        this.textoAula = textoAula;
    }

    public String getCodigo()
    {
        return this.codigo;
    }

    public String getEmenta()
    {
        return this.ementa;
    }

    public String getTextoAula()
    {
        return this.textoAula;
    }

    public String getHorario()
    {
        return this.horario;
    }

    public String getInfo()
    {
        return "Codigo: " + this.getCodigo() + "\nEmenta: " + this.getEmenta() + "\nHorario: " + this.getHorario() + "\n";
    }

}
