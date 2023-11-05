struct Pertag {
	unsigned int curtag; /* current tag index */
	int nmasters[NUMTAGS + 1]; /* number of windows in master area */
	int nstacks[NUMTAGS + 1]; /* number of windows in primary stack area */
	int ltaxis[NUMTAGS + 1][LTAXIS_LAST];
	const Layout *ltidxs[NUMTAGS + 1][3]; /* matrix of tags and layouts indexes  */
	float mfacts[NUMTAGS + 1]; /* mfacts per tag */
	unsigned int sellts[NUMTAGS + 1]; /* selected layouts */
	int showbars[NUMTAGS + 1]; /* display bar for the current tag */
};

void
pertagview(const Arg *arg)
{
	int i;

	if (arg->ui == ~SPTAGMASK)
		selmon->pertag->curtag = 0;
	else {
		for (i = 0; !(selmon->tagset[selmon->seltags] & 1 << i); i++);
		selmon->pertag->curtag = i + 1;
	}

	selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag];
	selmon->nstack = selmon->pertag->nstacks[selmon->pertag->curtag];
	selmon->mfact = selmon->pertag->mfacts[selmon->pertag->curtag];
	selmon->sellt = selmon->pertag->sellts[selmon->pertag->curtag];
	selmon->lt[selmon->sellt] = selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt];
	selmon->lt[selmon->sellt^1] = selmon->pertag->ltidxs[selmon->pertag->curtag][selmon->sellt^1];


	selmon->ltaxis[LAYOUT] = selmon->pertag->ltaxis[selmon->pertag->curtag][LAYOUT];
	selmon->ltaxis[MASTER] = selmon->pertag->ltaxis[selmon->pertag->curtag][MASTER];
	selmon->ltaxis[STACK]  = selmon->pertag->ltaxis[selmon->pertag->curtag][STACK];
	selmon->ltaxis[STACK2] = selmon->pertag->ltaxis[selmon->pertag->curtag][STACK2];
	if (selmon->showbar != selmon->pertag->showbars[selmon->pertag->curtag])
		togglebar(NULL);
}

