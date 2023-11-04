void
resetlayout(const Arg *arg)
{
    // NOTE: arg->ui ==
    // case 0: If focusing master, reset mfact and master clients' cfact.
    //         If not focusing master, reset not-master clients' cfact.
    // case 1: Same as 0, but if focusing master, also reset nmaster, else, nothing more.
    // case 2: Reset all. That is: reset mfact, nmaster, and all client's cfact.
    // case 3: Same as case 2, but also reset layout.
	// Arg default_mfact = {.f = mfact + 1};
	Arg default_layout = {.v = &layouts[0]};
    Client *c;
    int i, current_in_master = 0;
    unsigned int curtag = selmon->pertag->curtag;

    if(!selmon->lt[selmon->sellt]->arrange)
        return;

    if (arg->ui < 2) {
        // Check if current select client is in master area.
        for (i = -1, c = nexttiled(selmon->clients); c; c = nexttiled(c->next)) {
            // If the reading client not in current tag, skip it.
            if (!(c->tags & curtag))
                continue;
            i++;
            // If we find out current select client is in master area:
            if (c == selmon->sel && i < selmon->pertag->nmasters[curtag]) {
                current_in_master = 1;
                break;
            }
        }
    }

    for (i = -1, c = nexttiled(selmon->clients); c; c = nexttiled(c->next)) {
        // If not in current tag, skip it.
        if (!(c->tags & curtag))
            continue;
        i++;
        if (arg->ui < 2) {
            // If current selecting client is not in master but reading master clients now.
            if (!current_in_master && i < selmon->pertag->nmasters[curtag])
                continue;
            // If current selecting client is in master but ranched all masters.
            if (current_in_master && i == selmon->pertag->nmasters[curtag])
                break;
        }
        c->cfact = 1.0;
    }
    if (current_in_master || arg->ui > 1) {
        // setmfact
        selmon->mfact = selmon->pertag->mfacts[curtag] = mfact;
        if (arg->ui)
            // setnmaster
            selmon->nmaster = selmon->pertag->nmasters[curtag] = nmaster;
    }
    if (arg->ui > 2) {
        setlayout(&default_layout);
        return;
    }
    arrange(selmon);
}

