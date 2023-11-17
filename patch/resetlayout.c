void
resetlayout(const Arg *arg)
{
	setlayout(&(const Arg) { .v = &layouts[0] });
	setmfact(&(const Arg){ .f = mfact + 1 });
	#if PERTAG_PATCH
	selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag] = nmaster;
	#else
	selmon->nmaster = nmaster;
	#endif // PERTAG_PATCH
	if (selmon->showbar != showbar)
		togglebar(NULL);
}
