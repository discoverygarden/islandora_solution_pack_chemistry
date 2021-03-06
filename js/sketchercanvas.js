(function ($) {
    Drupal.behaviors.islandora_chemistry_sketcher_canvas = {
        attach: function (context, settings) {
            var chem_settings = settings.islandora_chemistry_sketcher_canvas;
            $(chem_settings.element_selector, context).once('islandora_chemistry_sketcher_canvas', function (index, element) {
                var canvas = new ChemDoodle.SketcherCanvas(element.id, chem_settings.width, chem_settings.height, {isMobile: $.browser.mobile, oneMolecule: true});
                canvas.specs.atoms_displayTerminalCarbonLabels_2D = true;
                canvas.specs.atoms_useJMOLColors = true;
                canvas.specs.bonds_clearOverlaps_2D = true;
                canvas.specs.bonds_overlapClearWidth_2D = 2;
                var starting_value = $(chem_settings.hidden_field_selector).val();
                if (starting_value) {
                  var starting_mol = ChemDoodle.readMOL(starting_value);
                  canvas.loadMolecule(starting_mol);
                }
                canvas.repaint();
                chem_settings.grab_structure = function() {
                    var mol = canvas.getMolecule();
                    var wmol = new ChemDoodle.io.MOLInterpreter();
                    $(chem_settings.hidden_field_selector).val(wmol.write(mol));
                }
                // This is to handle a poorly understood Safari rendering bug where the second
                // row of buttons will render each button on it's own row.
                setTimeout(function() {
                  $('.ui-helper-hidden-accessible').css('position', 'relative');
                }, 2000);
            });
        }
    };
})(jQuery);
