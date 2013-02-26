#ifndef __p4log_h_
#define __p4log_h_

#define LOGFILE "labrys"

//you don't need to change the following unless you need data longer than 4 digits
//or if you need names longer than 10 characters(for longer names you need only change MAX_NAME_WIDTH and filelines below)
#define MAX_NAME_WIDTH 10
#define LINE_LENGTH (MAX_NAME_WIDTH + 11)
#define WIN_OFFSET MAX_NAME_WIDTH
#define LOSS_OFFSET (MAX_NAME_WIDTH + 5)

#define FILE_LENGTH 14//change this if you change overall number of matchups

#define HORIZONTAL_LINE "-"//if you'd like the table styled differently

//input is matched against these names, so change them if you'd like to input using a shortened or different name
//whitespace must match the *_OFFSET, MAX_NAME_WIDTH, and LINE_LENGTH above.
static char *filelines[FILE_LENGTH] = {
  "labrys    0    0    \n",
  "aigis     0    0    \n",
  "naoto     0    0    \n",
  "mitsuru   0    0    \n",
  "yukiko    0    0    \n",
  "yousuke   0    0    \n",
  "narukami  0    0    \n",
  "elizabeth 0    0    \n",
  "chie      0    0    \n",
  "kanji     0    0    \n",
  "akihiko   0    0    \n",
  "teddie    0    0    \n",
  "slabrys   0    0    \n",
  "total     0    0    \n"
};

#endif
