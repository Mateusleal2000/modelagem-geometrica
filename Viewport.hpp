#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport{
  //matriz de cores
  public:
    int getLines();
    int getColumns();
    void setLines(int l);
    void setColumns(int c);
  //   void setColor(int l, int c, RGBColor color);
  //   RGBColor getColor(int l, int c);
  private:
    int l;
    int c;
};

#endif