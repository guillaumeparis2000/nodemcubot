// LOOP SLEEP IN MS
#define LOOPSLEEP 50 // Always less than 1000

const int TICKETSSECOND = 1000/LOOPSLEEP;

// Scheduler frequencies
const int EVERY_60_SECONDS = TICKETSSECOND*60;
const int EVERY_10_SECONDS = TICKETSSECOND*10;
const int EVERY_6_SECONDS  = TICKETSSECOND*6;
const int EVERY_4_SECONDS  = TICKETSSECOND*4;
const int EVERY_SECOND     = TICKETSSECOND*1;
const int EVERY_1_HOUR     = TICKETSSECOND*60*60;
const int EVERY_30_MINUTES = TICKETSSECOND*60*30;
