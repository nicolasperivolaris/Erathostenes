.PHONY: clean All

All:
	@echo "----------Building project:[ ErathostenesDyna - Debug ]----------"
	@cd "Erathostenes" && "$(MAKE)" -f  "ErathostenesDyna.mk"
clean:
	@echo "----------Cleaning project:[ ErathostenesDyna - Debug ]----------"
	@cd "Erathostenes" && "$(MAKE)" -f  "ErathostenesDyna.mk" clean
