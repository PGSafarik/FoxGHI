.PHONY: clean All

All:
	@echo "----------Sestavování projektu:[ FXGHI - Debug ]----------"
	@"$(MAKE)" -f  "FXGHI.mk"
clean:
	@echo "----------Čištění projektu:[ FXGHI - Debug ]----------"
	@"$(MAKE)" -f  "FXGHI.mk" clean
