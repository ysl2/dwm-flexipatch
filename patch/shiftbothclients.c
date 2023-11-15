void
shiftbothclients(const Arg *arg)
{
	Arg shifted = shift(arg, 1);
	tag(&shifted);
	view(&shifted);
}
